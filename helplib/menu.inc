/**
 * Name:            Helper Library
 * =============================================================================
 * Module:          Menu
 * Version:         1.0.0.0
 * Date of update:  05/30/2019
 * Contributor:     Exle / http://steamcommunity.com/profiles/76561198013509278/
 * =============================================================================
 */

#if !defined HELPLIB_HELPLIB_MENU_INC_
#define HELPLIB_HELPLIB_MENU_INC_

#include <helplib/translation>

stock void HelpLib_AddMenuText(Menu menu, char[] str) {
  int  count, style;
  char info[PLATFORM_MAX_PATH], buffer[PLATFORM_MAX_PATH];

  if ( !(count = menu.ItemCount) ) {
    menu.GetTitle(buffer, sizeof(buffer));
  } else {
    menu.GetItem(count - 1, info, sizeof(info), style, buffer, sizeof(buffer));
  }

  buffer[strlen(buffer)] = 0xA;
  StrCat(buffer, sizeof(buffer), str);

  if ( !count ) {
    menu.SetTitle(buffer);
  } else {
    menu.InsertItem(count - 1, info, buffer, style);
    menu.RemoveItem(count);
  }
}

stock void HelpLib_SetTranslatedTitle(Menu menu, int client,
                                      const char[] title) {
  if ( TranslationPhraseExists(title) ) {
    menu.SetTitle("%T", title, client);
  } else {
    menu.SetTitle("%s", title);
  }
}

stock void HelpLib_AddTranslatedText(Menu menu, int client,
                                     const char[] phrase) {
  char buffer[PLATFORM_MAX_PATH];
  HelpLib_TranslatePhraseEx(client, phrase, buffer, sizeof(buffer));

  HelpLib_AddMenuText(menu, buffer);
}

stock void HelpLib_AddTranslatedItem(Menu menu, int client, const char[] info,
                                     const char[] phrase,
                                     int style = ITEMDRAW_DEFAULT) {
  char buffer[PLATFORM_MAX_PATH];
  HelpLib_TranslatePhraseEx(client, phrase, buffer, sizeof(buffer));

  menu.AddItem(info, buffer, style);
}

#endif  // HELPLIB_HELPLIB_MENU_INC_
