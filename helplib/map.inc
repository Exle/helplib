/**
 * Name:            Helper Library
 * =============================================================================
 * Module:          Map
 * Version:         1.0.0.0
 * Date of update:  05/30/2019
 * Contributor:     Exle / http://steamcommunity.com/profiles/76561198013509278/
 * =============================================================================
 */

#if !defined HELPLIB_HELPLIB_MAP_INC_
#define HELPLIB_HELPLIB_MAP_INC_

stock void HelpLib_GetCurrentMapName(char[] buffer, int maxlength) {
  GetCurrentMap(buffer, maxlength);
  GetMapDisplayName(buffer, buffer, maxlength);
}

stock char[] HelpLib_GetCurrentMapNameA() {
  char buffer[PLATFORM_MAX_PATH];
  HelpLib_GetCurrentMapName(buffer, sizeof(buffer));
  return buffer;
}
#endif  // HELPLIB_HELPLIB_MAP_INC_
