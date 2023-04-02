/**
 * Name:            Helper Library
 * =============================================================================
 * Module:          Translation
 * Version:         1.0.0.0
 * Date of update:  05/30/2019
 * Contributor:     Exle / http://steamcommunity.com/profiles/76561198013509278/
 * =============================================================================
 */

#if !defined HELPLIB_HELPLIB_TRANSLATION_INC_
#define HELPLIB_HELPLIB_TRANSLATION_INC_

stock void HelpLib_LoadTranslations(const char[] file) {
  char buffer[PLATFORM_MAX_PATH];
  strcopy(buffer, sizeof(buffer), "../../../");
  StrCat(buffer, sizeof(buffer), file);
  LoadTranslations(buffer);
}

stock void HelpLib_TranslatePhrase(int client, const char[] phrase,
                                   char[] buffer, int maxlength) {
  if ( TranslationPhraseExists(phrase) ) {
    Format(buffer, maxlength, "%T", phrase, client);
  } else {
    strcopy(buffer, maxlength, phrase);
  }
}

stock char[] HelpLib_TranslatePhraseA(int client, const char[] phrase) {
  char buffer[PLATFORM_MAX_PATH];

  if ( TranslationPhraseExists(phrase) ) {
    Format(buffer, sizeof(buffer), "%T", phrase, client);
  } else {
    strcopy(buffer, sizeof(buffer), phrase);
  }

  return buffer;
}

stock void HelpLib_TranslatePhraseEx(int client, const char[] phrase,
                                     char[] buffer, int maxlength) {
  if ( TranslationPhraseExists(phrase) ) {
    FormatEx(buffer, maxlength, "%T", phrase, client);
  } else {
    strcopy(buffer, maxlength, phrase);
  }
}

stock char[] HelpLib_TranslatePhraseExA(int client, const char[] phrase) {
  char buffer[PLATFORM_MAX_PATH];

  if ( TranslationPhraseExists(phrase) ) {
    FormatEx(buffer, sizeof(buffer), "%T", phrase, client);
  } else {
    strcopy(buffer, sizeof(buffer), phrase);
  }

  return buffer;
}

#endif  // HELPLIB_HELPLIB_TRANSLATION_INC_
