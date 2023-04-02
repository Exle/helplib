/**
 * Name:            Helper Library
 * =============================================================================
 * Module:          KeyValues
 * Version:         1.0.0.0
 * Date of update:  01/12/2021
 * Contributor:     Exle / http://steamcommunity.com/profiles/76561198013509278/
 * =============================================================================
 */

#if !defined HELPLIB_HELPLIB_KEYVALUES_INC_
#define HELPLIB_HELPLIB_KEYVALUES_INC_

/**
 * Retrieves a string value from a KeyValues key.
 *
 * @param kv            KeyValues Handle.
 * @param key           Name of the key, or NULL_STRING.
 * @param defvalue      Optional default value to use if the key is not found.
 * @return              String value of the key.
 * @error               Invalid Handle.
 */
stock char[] HelpLib_KvGetString(Handle kv, const char[] key,
                                 const char[] defvalue = "") {
  char buffer[PLATFORM_MAX_PATH];
  KvGetString(kv, key, buffer, sizeof(buffer), defvalue);
  return buffer;
}

/**
 * Retrieves a set of color values from a KeyValues key.
 *
 * @param kv            KeyValues Handle.
 * @param key           Name of the key, or NULL_STRING.
 * @return              Integer array value of the key.
 * @error               Invalid Handle.
 */
stock int[] HelpLib_KvGetColor(Handle kv, const char[] key) {
  int buffer[4];
  KvGetColor(kv, key, buffer[0], buffer[1], buffer[2], buffer[3]);
  return buffer;
}

/**
 * Retrieves a large integer value from a KeyValues key.
 *
 * @param kv            KeyValues Handle.
 * @param key           Name of the key, or NULL_STRING.
 * @param defvalue      Optional default value to use if the key is not found.
 * @return              Integer array value of the key.
 * @error               Invalid Handle.
 */
stock int[] HelpLib_KvGetUInt64(Handle kv, const char[] key,
                                int    defvalue[2] = { 0, 0 }) {
  int buffer[2];
  KvGetUInt64(kv, key, buffer, defvalue);
  return buffer;
}

/**
 * Retrieves a vector value from a KeyValues key.
 *
 * @param kv            KeyValues Handle.
 * @param key           Name of the key, or NULL_STRING.
 * @param defvalue      Optional default value to use if the key is not found.
 * @return              Float array value of the key.
 * @error               Invalid Handle.
 */
stock float[] HelpLib_KvGetVector(Handle      kv, const char[] key,
                                  const float defvalue[3] = { 0.0, 0.0, 0.0 }) {
  float buffer[3];
  KvGetVector(kv, key, buffer, defvalue);
  return buffer;
}

#endif  // HELPLIB_HELPLIB_KEYVALUES_INC_
