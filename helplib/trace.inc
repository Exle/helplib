/**
 * Name:            Helper Library
 * =============================================================================
 * Module:          Trace
 * Version:         1.0.0.0
 * Date of update:  05/30/2019
 * Contributor:     Exle / http://steamcommunity.com/profiles/76561198013509278/
 * =============================================================================
 */

#if !defined HELPLIB_HELPLIB_TRACE_INC_
#define HELPLIB_HELPLIB_TRACE_INC_

#include <sdktools_engine>
#include <sdktools_functions>
#include <sdktools_trace>

stock void HelpLib_ClientGetRayEndPosition(int client, float output[3]) {
  float angles[3];

  GetClientEyePosition(client, output);
  GetClientEyeAngles(client, angles);

  TR_TraceRayFilter(output, angles, MASK_SHOT, RayType_Infinite,
                    HelpLib_FilterNoClients, client);

  if ( TR_DidHit() ) {
    TR_GetEndPosition(output);
  }
}

stock float[] HelpLib_ClientGetRayEndPositionA(int client) {
  float output[3];
  HelpLib_ClientGetRayEndPosition(client, output);
  return output;
}

stock bool HelpLib_FilterNoClients(int entity, int contentsMask, any data) {
  return (entity != data && !(0 < data <= MaxClients));
}

#endif  // HELPLIB_HELPLIB_TRACE_INC_
