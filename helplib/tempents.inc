/**
 * Name:            Helper Library
 * =============================================================================
 * Module:          Tempents
 * Version:         1.0.0.0
 * Date of update:  05/30/2019
 * Contributor:     Exle / http://steamcommunity.com/profiles/76561198013509278/
 * =============================================================================
 */

#if !defined HELPLIB_HELPLIB_TEMPENTS_INC_
#define HELPLIB_HELPLIB_TEMPENTS_INC_

#include <sdktools_tempents>
#include <sdktools_tempents_stocks>

#define HELPLIB_TE_NONE           0
#define HELPLIB_TE_ALL            (1 << 0)
#define HELPLIB_TE_ALIVE          (1 << 1)
#define HELPLIB_TE_DEAD           (1 << 2)
#define HELPLIB_TE_TEAM_SPEC      (1 << 3)
#define HELPLIB_TE_TEAM_T         (1 << 4)
#define HELPLIB_TE_TEAM_CT        (1 << 5)
#define HELPLIB_TE_CLIENTS        (1 << 6)

#define HELPLIB_TE_CLIENT(% 0)    ((% 0 & 0xFF) | (HELPLIB_TE_CLIENTS << 8))
#define HELPLIB_TE_GETCLIENT(% 0) (% 0 & 0xFF)
#define HELPLIB_TE_GETFLAG(% 0)   (% 0 >> 8)

stock void HelpLib_DrawBox(int flags = HELPLIB_TE_NONE, float pnt1[3],
                           float pnt2[3], float delay = 0.0, int model,
                           int halo = 0, int start_frame = 0,
                           int frame_rate = 35, float life = 1.0,
                           float width = 1.0, float end_width = 1.0,
                           int fade_length = 10, float amplitude = 0.0,
                           const int color[4] = { 255, 255, 255, 255 },
                           int       speed    = 2) {
  float points[6];
  for ( int i = 0; i < sizeof(points); i++ ) {
    points[i] = i >= sizeof(pnt1) ? pnt2[i - 3] : pnt1[i];
  }

  int phase[][] = {
    { 0, 1, 2, 0, 4, 2 },
    { 0, 4, 2, 3, 4, 2 },
    { 3, 4, 2, 3, 1, 2 },
    { 3, 1, 2, 0, 1, 2 },

    { 0, 1, 5, 0, 4, 5 },
    { 0, 4, 5, 3, 4, 5 },
    { 3, 4, 5, 3, 1, 5 },
    { 3, 1, 5, 0, 1, 5 },

    { 0, 1, 2, 0, 1, 5 },
    { 0, 4, 2, 0, 4, 5 },
    { 3, 4, 2, 3, 4, 5 },
    { 3, 1, 2, 3, 1, 5 }
  };

  float point[2][3];

  for ( int a, b, c; a < sizeof(phase); a++ ) {
    for ( b = 0; b < sizeof(point); b++ ) {
      for ( c = 0; c < sizeof(point[]); c++ ) {
        point[b][c] = points[phase[a][b * sizeof(point[]) + c]];
      }
    }

    HelpLib_BeamPoints(flags, point[0], point[1], delay, model, halo,
                       start_frame, frame_rate, life, width, end_width,
                       fade_length, amplitude, color, speed);
  }
}

stock void HelpLib_DrawBoxA(int flags = HELPLIB_TE_NONE, float pnt1[3],
                            float pnt2[3], float delay = 0.0, char[] model = "",
                            char[] halo = "", int start_frame = 0,
                            int frame_rate = 35, float life = 1.0,
                            float width = 1.0, float end_width = 1.0,
                            int fade_length = 10, float amplitude = 0.0,
                            const int color[4] = { 255, 255, 255, 255 },
                            int       speed    = 2) {
  if ( strlen(model) ) {
    HelpLib_DrawBox(flags, pnt1, pnt2, delay, PrecacheModel(model),
                    !strlen(halo) ? 0 : PrecacheModel(halo), start_frame,
                    frame_rate, life, width, end_width, fade_length, amplitude,
                    color, speed);
  }
}

stock void HelpLib_BeamPoints(int flags = HELPLIB_TE_NONE, float start[3],
                              float end[3], float delay = 0.0, int model,
                              int halo = 0, int start_frame = 0,
                              int frame_rate = 35, float life,
                              float width = 1.0, float end_width = 1.0,
                              int fade_length = 10, float amplitude = 0.0,
                              const int color[4] = { 255, 255, 255, 255 },
                              int       speed    = 2) {
  TE_SetupBeamPoints(start, end, model, halo, start_frame, frame_rate, life,
                     width, end_width, fade_length, amplitude, color, speed);
  HelpLib_TESend(flags, delay);
}

stock void HelpLib_BeamPointsA(
  int flags = HELPLIB_TE_NONE, float start[3], float end[3], float delay = 0.0,
  char[] model = "", char[] halo = "", int start_frame = 0, int frame_rate = 35,
  float life, float width = 1.0, float end_width = 1.0, int fade_length = 10,
  float amplitude = 0.0, const int color[4] = { 255, 255, 255, 255 },
  int speed = 2) {
  HelpLib_BeamPoints(flags, start, end, delay, PrecacheModel(model),
                     !strlen(halo) ? 0 : PrecacheModel(halo), start_frame,
                     frame_rate, life, width, end_width, fade_length, amplitude,
                     color, speed);
}

stock void HelpLib_DrawCross(int flags = HELPLIB_TE_NONE, int size = 4,
                             float pos[3], float delay = 0.0, int model,
                             int halo = 0, int start_frame = 0,
                             int frame_rate = 35, float life = 1.0,
                             float width = 1.0, int fade_length = 10,
                             float amplitude = 0.0, int speed = 2) {
  float ray1[3];
  float ray2[3];

  int   colors[][] = {
    {255, 0,   0,   255},
    { 0,  255, 0,   255},
    { 0,  0,   255, 255}
  };

  for ( int i = 0; i < 3; i++ ) {
    ray1 = pos;
    ray2 = pos;

    ray1[i] -= size;
    ray2[i] += size;

    TE_SetupBeamPoints(ray1, ray2, model, halo, start_frame, frame_rate, life,
                       width, width, fade_length, amplitude, colors[i], speed);
    HelpLib_TESend(flags, delay);
  }
}

stock void HelpLib_DrawCrossA(int flags = HELPLIB_TE_NONE, int size = 4,
                              float pos[3], float delay             = 0.0,
                              char[] model = "", char[] halo = "",
                              int start_frame = 0, int frame_rate = 35,
                              float life = 1.0, float width = 1.0,
                              int fade_length = 10, float amplitude = 0.0,
                              int speed = 2) {
  HelpLib_DrawCross(flags, size, pos, delay, PrecacheModel(model),
                    !strlen(halo) ? 0 : PrecacheModel(halo), start_frame,
                    frame_rate, life, width, fade_length, amplitude, speed);
}

stock void HelpLib_TESend(int flags = HELPLIB_TE_NONE, float delay = 0.0) {
  int total     = 0;
  int[] clients = new int[MaxClients];
  if ( flags ) {
    if ( HELPLIB_TE_GETFLAG(flags) & HELPLIB_TE_CLIENTS ) {
      clients[total++] = HELPLIB_TE_GETCLIENT(flags);
    } else {
      for ( int i = 1; i <= MaxClients; i++ ) {
        if ( !IsClientInGame(i)
             || !(flags & HELPLIB_TE_ALL)
                  && (flags & HELPLIB_TE_ALIVE && !IsPlayerAlive(i)
                      || flags & HELPLIB_TE_DEAD && IsPlayerAlive(i)
                      || flags & HELPLIB_TE_TEAM_SPEC && GetClientTeam(i) != 1
                      || flags & HELPLIB_TE_TEAM_T && GetClientTeam(i) != 2
                      || flags & HELPLIB_TE_TEAM_CT
                           && GetClientTeam(i) != 3) ) {
          continue;
        }
        clients[total++] = i;
      }
    }
  }
  TE_Send(clients, total, delay);
}

stock void HelpLib_DrawBoxC(const int[] clients, int numClients, float pnt1[3],
                            float pnt2[3], float delay = 0.0, int model,
                            int halo = 0, int start_frame = 0,
                            int frame_rate = 35, float life = 1.0,
                            float width = 1.0, float end_width = 1.0,
                            int fade_length = 10, float amplitude = 0.0,
                            const int color[4] = { 255, 255, 255, 255 },
                            int       speed    = 2) {
  if ( !model ) {
    return;
  }

  float points[6];
  for ( int i = 0; i < sizeof(points); i++ ) {
    points[i] = i >= sizeof(pnt1) ? pnt2[i - 3] : pnt1[i];
  }

  int phase[][] = {
    { 0, 1, 2, 0, 4, 2 },
    { 0, 4, 2, 3, 4, 2 },
    { 3, 4, 2, 3, 1, 2 },
    { 3, 1, 2, 0, 1, 2 },

    { 0, 1, 5, 0, 4, 5 },
    { 0, 4, 5, 3, 4, 5 },
    { 3, 4, 5, 3, 1, 5 },
    { 3, 1, 5, 0, 1, 5 },

    { 0, 1, 2, 0, 1, 5 },
    { 0, 4, 2, 0, 4, 5 },
    { 3, 4, 2, 3, 4, 5 },
    { 3, 1, 2, 3, 1, 5 }
  };

  float point[2][3];

  for ( int a, b, c; a < sizeof(phase); a++ ) {
    for ( b = 0; b < sizeof(point); b++ ) {
      for ( c = 0; c < sizeof(point[]); c++ ) {
        point[b][c] = points[phase[a][b * sizeof(point[]) + c]];
      }
    }

    HelpLib_BeamPointsC(clients, numClients, point[0], point[1], delay, model,
                        halo, start_frame, frame_rate, life, width, end_width,
                        fade_length, amplitude, color, speed);
  }
}

stock void HelpLib_DrawBoxAC(
  const int[] clients, int numClients, float pnt1[3], float pnt2[3],
  float delay = 0.0, char[] model = "", char[] halo = "", int start_frame = 0,
  int frame_rate = 35, float life = 1.0, float width = 1.0,
  float end_width = 1.0, int fade_length = 10, float amplitude = 0.0,
  const int color[4] = { 255, 255, 255, 255 }, int speed = 2) {
  HelpLib_DrawBoxC(clients, numClients, pnt1, pnt2, delay,
                   !strlen(model) ? 0 : PrecacheModel(model),
                   !strlen(halo) ? 0 : PrecacheModel(halo), start_frame,
                   frame_rate, life, width, end_width, fade_length, amplitude,
                   color, speed);
}

stock void HelpLib_BeamPointsC(const int[] clients, int numClients,
                               float start[3], float end[3], float delay = 0.0,
                               int model, int halo = 0, int start_frame = 0,
                               int frame_rate = 35, float life,
                               float width = 1.0, float end_width = 1.0,
                               int fade_length = 10, float amplitude = 0.0,
                               const int color[4] = { 255, 255, 255, 255 },
                               int       speed    = 2) {
  if ( model ) {
    TE_SetupBeamPoints(start, end, model, halo, start_frame, frame_rate, life,
                       width, end_width, fade_length, amplitude, color, speed);
    TE_Send(clients, numClients, delay);
  }
}

stock void HelpLib_BeamPointsAC(
  const int[] clients, int numClients, float start[3], float end[3],
  float delay = 0.0, char[] model = "", char[] halo = "", int start_frame = 0,
  int frame_rate = 35, float life, float width = 1.0, float end_width = 1.0,
  int fade_length = 10, float amplitude = 0.0,
  const int color[4] = { 255, 255, 255, 255 }, int speed = 2) {
  HelpLib_BeamPointsC(clients, numClients, start, end, delay,
                      !strlen(model) ? 0 : PrecacheModel(model),
                      !strlen(halo) ? 0 : PrecacheModel(halo), start_frame,
                      frame_rate, life, width, end_width, fade_length,
                      amplitude, color, speed);
}

stock void HelpLib_DrawCrossC(const int[] clients, int numClients, int size = 4,
                              float pos[3], float delay = 0.0, int model,
                              int halo = 0, int start_frame = 0,
                              int frame_rate = 35, float life = 1.0,
                              float width = 1.0, int fade_length = 10,
                              float amplitude = 0.0, int speed = 2) {
  if ( !model ) { return; }

  float ray1[3];
  float ray2[3];

  int   colors[][] = {
    { 255, 0,   0,   255 },
    { 0,   255, 0,   255 },
    { 0,   0,   255, 255 }
  };

  for ( int i = 0; i < 3; i++ ) {
    ray1 = pos;
    ray2 = pos;

    ray1[i] -= size;
    ray2[i] += size;

    TE_SetupBeamPoints(ray1, ray2, model, halo, start_frame, frame_rate, life,
                       width, width, fade_length, amplitude, colors[i], speed);
    TE_Send(clients, numClients, delay);
  }
}

stock void HelpLib_DrawCrossAC(const int[] clients, int numClients,
                               int size = 4, float pos[3], float delay = 0.0,
                               char[] model = "", char[] halo = "",
                               int start_frame = 0, int frame_rate = 35,
                               float life = 1.0, float width = 1.0,
                               int fade_length = 10, float amplitude = 0.0,
                               int speed = 2) {
  int model = !strlen(model) ? 0 : PrecacheModel(model);
  int halo  = !strlen(halo) ? 0 : PrecacheModel(halo);

  HelpLib_DrawCrossC(clients, numClients, size, pos, delay, model, halo,
                     start_frame, frame_rate, life, width, fade_length,
                     amplitude, speed);
}

#endif  // HELPLIB_HELPLIB_TEMPENTS_INC_
