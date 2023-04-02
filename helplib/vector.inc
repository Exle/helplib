/**
 * Name:            Helper Library
 * =============================================================================
 * Module:          Vector
 * Version:         1.0.0.0
 * Date of update:  05/30/2019
 * Contributor:     Exle / http://steamcommunity.com/profiles/76561198013509278/
 * =============================================================================
 */

#if !defined HELPLIB_HELPLIB_VECTOR_INC_
#define HELPLIB_HELPLIB_VECTOR_INC_

stock void HelpLib_SnapToGrid(float pos[3], float output[3], int grid,
                              bool third = true) {
  output    = pos;

  output[0] = float(RoundToNearest(pos[0] / grid) * grid);
  output[1] = float(RoundToNearest(pos[1] / grid) * grid);

  if ( third ) {
    output[2] = float(RoundToNearest(pos[2] / grid) * grid);
  }
}

stock float[] HelpLib_SnapToGridA(float pos[3], int grid, bool third = true) {
  float output[3];
  HelpLib_SnapToGrid(pos, output, grid, third);
  return output;
}

stock bool HelpLib_IsEmptyVector(float vec[3]) {
  return (IsNullVector(vec)
          || (vec[0] == 0.0 && vec[1] == 0.0 && vec[2] == 0.0));
}

stock void HelpLib_GetMiddleFromTwoPoints(float pnt1[3], float pnt2[3],
                                          float output[3]) {
  for ( int i = 0; i < 3; i++ ) {
    output[i] = (pnt1[i] + pnt2[i]) / 2.0;
  }
}

stock float[] HelpLib_GetMiddleFromTwoPointsA(float pnt1[3], float pnt2[3]) {
  float output[3];
  HelpLib_GetMiddleFromTwoPoints(pnt1, pnt2, output);
  return output;
}

stock void HelpLib_GetHalfVector(float pnt1[3], float pnt2[3],
                                 float output[3]) {
  MakeVectorFromPoints(pnt2, pnt1, output);

  for ( int i = 0; i < 3; i++ ) {
    output[i] /= 2.0;
    if ( output[i] < 0.0 ) {
      output[i] = -output[i];
    }
  }
}

stock float[] HelpLib_GetHalfVectorA(float pnt1[3], float pnt2[3]) {
  float output[3];
  HelpLib_GetHalfVector(pnt1, pnt2, output);
  return output;
}

stock void HelpLib_CopyVector(float vec1[3], float vec2[3]) {
  for ( int i = 0; i < 3; i++ ) {
    vec1[i] = vec2[i];
  }
}

stock float[] HelpLib_CopyVectorA(float vec[3]) {
  float output[3];
  HelpLib_CopyVector(vec, output);
  return output;
}

#endif  // HELPLIB_HELPLIB_VECTOR_INC_
