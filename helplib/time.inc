/**
 * Name:            Helper Library
 * =============================================================================
 * Module:          Time
 * Version:         1.0.0.0
 * Date of update:  01/14/2021
 * Contributor:     Exle / http://steamcommunity.com/profiles/76561198013509278/
 * =============================================================================
 */

#if !defined HELPLIB_HELPLIB_TIME_INC_
#define HELPLIB_HELPLIB_TIME_INC_

// Changed function by Kailo
// (https://hlmod.ru/threads/sklad-funkcij-sourcepawn.45161/#post-377974)
stock void HelpLib_GetStringTime(float time, char[] buffer, int maxlength,
                                 bool precision = false) {
  int        itime  = RoundToNearest(time);
  static int dims[] = { 60, 60, 24, 30, 12, cellmax };
  buffer[0]         = EOS;

  if ( precision ) {
    FormatEx(buffer, maxlength, "%.3f", time - RoundToFloor(time));
    strcopy(buffer, maxlength, buffer[1]);
  }

  int  i = 0, f = -1;
  bool cond = false;
  while ( !cond ) {
    if ( f++ == 1 ) {
      cond = true;
    }

    do {
      Format(buffer, maxlength, !i ? "%02d%s" : "%02d:%s", itime % dims[i],
             buffer);
      if ( itime /= dims[i++], itime == 0 ) {
        return;
      }
    } while ( cond );
  }
}

#endif  // HELPLIB_HELPLIB_TIME_INC_
