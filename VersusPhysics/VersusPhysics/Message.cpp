#include "Message.h"

std::vector<std::string> MessageManager::TypeIDs;

const int MessageManager::GetTypeID(std::string MessageType)
{
	int CurrentID = IndexOf(MessageType);
	if (CurrentID < 0)
	{
		TypeIDs.push_back(MessageType);
		return TypeIDs.size() - 1;
	}
	else
	{
		return CurrentID;
	}

}

const int MessageManager::IndexOf(std::string MessageType)
{
	for (int Index = 0; Index < TypeIDs.size(); Index++)
	{
		if (TypeIDs[Index] == MessageType) {
			return Index;
		}
	}
	return -1;
}
