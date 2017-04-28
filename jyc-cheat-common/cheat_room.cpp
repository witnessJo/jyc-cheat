#include "cheat_room.hpp"

using namespace jyc_cheat;
using namespace std;
using json = nlohmann::json;

cheat_room::cheat_room(string name){
  this->room_name = name;
}

cheat_room::~cheat_room(){
}


int cheat_room::IsExistUser(cheat_user* user_to_find){
  if(this->map_users.find(user_to_find->GetNickName()) != this->map_users.end()){
    // exists user
    return 1;
  }
  // not exists user
  return 0;
}


int cheat_room::AddUser(cheat_user* added_user){
  if(added_user){
    string nick_name = added_user->GetNickName();
    if(map_users.find(nick_name) == map_users.end()){
      this->map_users[nick_name] = added_user;
    }
  }

 return 0;
}


int cheat_room::RemoveUser(cheat_user* user_to_remove){
  if(user_to_remove){
  }
  return 0;
}


int cheat_room::GetCurrentRoomMembers(list<cheat_user>* user_list){
  map<string, cheat_user*>::iterator iter;
  if(user_list){
    user_list->clear();
    for(iter = this->map_users.begin(); iter != this->map_users.end(); ++iter){
      user_list->push_back(*(iter->second));
    }
  }
  return 0;
}


int cheat_room::SendMessageToMembers(cheat_message* message){

  if(message){
    json json_recv = json::parse(message->GetMessage());
    string room_name = json_recv["room_name"].get<string>();
    string send_user = json_recv["nickname"].get<string>();
    string str_message = json_recv["message"].get<string>();

    json json_ret;
    json_ret["res_tag"] = "send_cheat_message";
    json_ret["send_user"] = send_user;
    json_ret["message"] = str_message;
    
    map<string, cheat_user*>::iterator iter;

    cout << "room's user size : " << this->map_users.size() << endl;
    for(iter = this->map_users.begin(); iter != this->map_users.end(); ++iter){
      if(iter->second->SendMessage(json_ret.dump()) == -1){
	// What I should handle something ?
      }
    }
  }
  return 0;
}

