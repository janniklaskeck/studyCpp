#include <fstream>
#include <sstream>
#include <string>
#include <stdint.h>

#include <SDL.h>
#include <GL\glew.h>

#include "Model.h"
#include "Matrix4.h"


// Some utility functions in this file to keep the code more readable
bool open_window(const char *title, uint16_t window_width, uint16_t window_height);
std::string read_file(const char* filename);
GLuint load_shader(GLenum shader_type, const char *filename);
void draw();
void close_window();


// OpenGL objects we need for drawing
GLuint program, vertex_buffer, index_buffer;
// Transformation and projection matrix
Matrix4 model_view, projection;
SDL_Window* Window;

int main(int argc, char* args[])
{
	uint16_t window_width = 640, window_height = 480;
	bool success;

	Model model("../models/darwinian.obj");

	// Open a window with an OpenGL context
	success = open_window("Renderer", window_width, window_height);
	if (!success)
		return 1;

	// Load the individual shaders (the paths are relative to the directory where your source code files are in)
	GLuint vertex_shader = load_shader(GL_VERTEX_SHADER, "shaders\\basic.vs");
	GLuint fragment_shader = load_shader(GL_FRAGMENT_SHADER, "shaders\\basic.fs");
	if (vertex_shader == 0 || fragment_shader == 0)
		return 1;

	// Combine the shaders into a pipeline we can use for rendering (OpenGL calls this a "program")
	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	// Upload the vertex data to the GPU
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);

	glBufferData(GL_ARRAY_BUFFER, model.vertices.size() * sizeof(Vector3D), model.vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Upload index data to the GPU
	glGenBuffers(1, &index_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.faces.size() * sizeof(Face), model.faces.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Tell OpenGL to only render wireframes. We'll do surfaces later.
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Initialize the camera (model_view) and projection matrix
	Vector3D camera_pos(2.5, 2.5, 5);
	model_view = Matrix4::lookAt(camera_pos, Vector3D(0, 0, 0), Vector3D(0, 1, 0));
	projection = Matrix4::projection(60, (float)window_height / window_width, 0.1f, 100);

	// The main loop: Here we react to different events like user input
	SDL_Event e;
	while (SDL_WaitEvent(&e))
	{
		// Break out of the main loop when the user closes the window
		if (e.type == SDL_QUIT)
			break;

		if (e.type == SDL_KEYDOWN)
		{
			// React to key down events: We change the x-position of our camera, update the
			// model_view matrix and redraw the screen.
			switch (e.key.keysym.sym)
			{
			case SDLK_LEFT:
				camera_pos.x -= 1;
				model_view = Matrix4::lookAt(camera_pos, Vector3D(0, 0, 0), Vector3D(0, 1, 0));
				break;
			case SDLK_RIGHT:
				camera_pos.x += 1;
				model_view = Matrix4::lookAt(camera_pos, Vector3D(0, 0, 0), Vector3D(0, 1, 0));
				break;
			case SDLK_DOWN:
				camera_pos.z -= 1;
				model_view = Matrix4::lookAt(camera_pos, Vector3D(0, 0, 0), Vector3D(0, 1, 0));
				break;
			case SDLK_UP:
				camera_pos.z += 1;
				model_view = Matrix4::lookAt(camera_pos, Vector3D(0, 0, 0), Vector3D(0, 1, 0));
				break;

				// TODO:
				// add additional keys for improved camera control
			default:
				break;
			}
		}
		draw();
	}

	// Delete our data buffers on the GPU
	glDeleteBuffers(1, &index_buffer);
	glDeleteBuffers(1, &vertex_buffer);

	// Delete the shaders
	glDeleteProgram(program);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	close_window();

	return 0;
}


void draw()
{
	// Clear the old image with the background color
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	// Use our shader program for the comming draw operation
	glUseProgram(program);

	// Use the vertex buffer data and tell how the position attribute is stored in the buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	GLint pos_attribute_location = glGetAttribLocation(program, "pos");
	glEnableVertexAttribArray(pos_attribute_location);
	glVertexAttribPointer(pos_attribute_location, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	// Set the uniforms for the comming draw operation
	GLint model_view_uniform_location = glGetUniformLocation(program, "model_view");
	glUniformMatrix4fv(model_view_uniform_location, 1, false, model_view.data);
	GLint projection_uniform_location = glGetUniformLocation(program, "projection");
	glUniformMatrix4fv(projection_uniform_location, 1, false, projection.data);

	// Use the indices in the index buffer for the next draw operation and query how many
	// bytes it contains (we need the number of indices in the buffer for the draw command).
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
	GLint index_buffer_size = 0;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &index_buffer_size);

	// Draw all indices in the index buffer (its size in bytes / bytes per index). This will
	// use the bound vertex buffer as attribute data and the bound index buffer to read the
	// indices.
	glDrawElements(GL_TRIANGLES, index_buffer_size / sizeof(uint32_t), GL_UNSIGNED_INT, 0);

	// Clear the bound buffers
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);

	// Display the rendered image on the screen
	SDL_GL_SwapWindow(Window);
}


/**
 * Opens an OpenGL window. This function has to be called before every other OpenGL function!
 * Otherwise OpenGL is not initialized and most OpenGL fuctions will be NULL-pointers. You can
 * only open one window with this function. SDL does not support multiple windows.
 */
bool open_window(const char *title, uint16_t window_width, uint16_t window_height)
{
	// Open a window with a basic OpenGL context using the SDL library
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	Window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_OPENGL);
	SDL_GL_CreateContext(Window);
	// Initialize functions from OpenGL 2.0 and newer
	if (glewInit() != GLEW_OK)
	{
		printf("OpenGL extention initialization failed...\n");
		return false;
	}

	return true;
}

void close_window()
{
	SDL_Quit();
}

/**
 * Reads shader source code from a file and creates an OpenGL shader for it. Use GL_VERTEX_SHADER
 * as shader_type to load a vertex shader and GL_FRAGMENT_SHADER to load a fragment shader.
 *
 * Returns the shaders GL object id on success or 0 on error. Compiler errors in the shader are
 * printed on stderr.
 */
GLuint load_shader(GLenum shader_type, const char *filename)
{
	// Read the shader source code from the file
	std::string shader_code = read_file(filename);
	if (shader_code.empty())
	{
		fprintf(stderr, "Could not load shader file %s\n", filename);
		return 0;
	}

	// Create a new shader that uses our shader source code. Tell OpenGL to comple the shader.
	GLuint shader = glCreateShader(shader_type);
	const GLchar* code[] = { shader_code.data() };
	const GLint length[] = { (GLint)shader_code.length() };
	glShaderSource(shader, 1, code, length);
	glCompileShader(shader);

	// Check if something was wrong with the shader.
	GLint result = GL_TRUE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		char message[1024];
		glGetShaderInfoLog(shader, sizeof(message), NULL, message);
		fprintf(stderr, "Shader compilation of %s failed:\n%s\n", filename, message);
		return 0;
	}

	return shader;
}

/**
 * Reads a file into a C++ string. Be aware: This function uses the rather complicated
 * C++ standard library because the simple C way is just to painful on Windows.
 *
 * If the file could not be read an empty string is returned.
 */
std::string read_file(const char* filename)
{
	std::ifstream in(filename, std::ios::in | std::ios::binary);
	if (!in)
		return std::string();

	std::ostringstream contents;
	contents << in.rdbuf();
	in.close();
	return contents.str();
}