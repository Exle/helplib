/**
 * Name:            Helper Library
 * =============================================================================
 * Module:          Chat
 * Version:         1.0.0.0
 * Date of update:  11/22/2021
 * Contributor:     Exle / http://steamcommunity.com/profiles/76561198013509278/
 * =============================================================================
 */

#if !defined HELPLIB_HELPLIB_CHAT_INC_
#define HELPLIB_HELPLIB_CHAT_INC_

stock void HelpLib_ChatMessage(int client, const char[] format, any...) {
  if ( !IsClientInGame(client) || IsFakeClient(client) ) {
    return;
  }

  char buffer[PLATFORM_MAX_PATH * 4];

  SetGlobalTransTarget(client);
  VFormat(buffer, sizeof(buffer), format, 3);
  HelpLib_SendMessage(client, buffer);
}

stock void HelpLib_ChatMessageAll(const char[] format, any...) {
  char buffer[PLATFORM_MAX_PATH * 4];

  for ( int client = 1; client <= MaxClients; client++ ) {
    if ( !IsClientInGame(client) || IsFakeClient(client) ) {
      continue;
    }

    SetGlobalTransTarget(client);
    VFormat(buffer, sizeof(buffer), format, 2);

    HelpLib_SendMessage(client, buffer);
  }
}

static stock void HelpLib_SendMessage(int client, char[] message,
                                      int author = 0) {
  if ( !author ) {
    author = client;
  }

  static EngineVersion engine = view_as<EngineVersion>(-1);
  if ( engine == view_as<EngineVersion>(-1) ) {
    engine = GetEngineVersion();
  }

  Format(message, PLATFORM_MAX_PATH * 4, "%s\x01%s",
         engine == Engine_CSGO ? " " : "", message);

  Handle msg =
    StartMessageOne("SayText2", client, USERMSG_RELIABLE | USERMSG_BLOCKHOOKS);

  if ( GetFeatureStatus(FeatureType_Native, "GetUserMessageType")
         != FeatureStatus_Available
       || GetUserMessageId("SayText2") == INVALID_MESSAGE_ID ) {
    PrintToChat(client, message);
    return;
  }

  if ( GetUserMessageType() == UM_Protobuf ) {
    Protobuf pb = UserMessageToProtobuf(msg);

    pb.SetInt("ent_idx", author);
    pb.SetBool("chat", true);
    pb.SetString("msg_name", message);
  } else {
    BfWrite bf = UserMessageToBfWrite(msg);

    bf.WriteByte(author);
    bf.WriteByte(true);
    bf.WriteString(message);
  }

  EndMessage();
}

#endif  // HELPLIB_HELPLIB_CHAT_INC_
