#include "misc.hxx"
//cppcheck-suppress unusedFunction
bool starts_with(const std::string & param, const std::string & what) {
	if (param.size() < what.size())
		return false;
	return !param.compare(0, what.size(), what);
}

void appendToResult(char* base_string, char* prefix, char* to_append,
		int max_result_length) {
	if (to_append != NULL && strlen(to_append) > 0) {
		if ((strlen(prefix) + strlen(to_append))
				< (max_result_length - strlen(base_string))) {
			strcat(base_string, prefix);
			strcat(base_string, to_append);
		}
	}
}

/***************************************************************
 *  STRCPY / 2007-11-22 / KPe                                   *
 ***************************************************************/
char *StrCpy(char *StrOut, /* O: Copy to this string */
int MaxStr, /* I: Size of string */
const char *StrIn) /* I: Copy this string */
{
	if (MaxStr <= 0)
		return (NULL);

	if (StrIn == NULL) {
		StrOut[0] = '\0';
		return (StrOut);
	}

	if (strlen(StrIn) < MaxStr - 1)
		strcpy(StrOut, StrIn);
	else {
		strncpy(StrOut, StrIn, MaxStr - 1);
		*(StrOut + MaxStr - 1) = '\0';
	}

	return (StrOut);
}
/***************************************************************
 *  STRUPR / 2007-11-28 / KPe                                   *
 ***************************************************************/
char *StrUpr(char *StrInOut) /* I&O: Change this string */
{
	char *pStrInOut;

	for (pStrInOut = StrInOut; *pStrInOut != '\0'; pStrInOut++)
		*pStrInOut = toupper(*pStrInOut);

	return (StrInOut);
}

/***************************************************************
 *  SHOWTCMESSAGE / 2007-11-22 / KPe                            *
 *                                                              *
 *  Show Teamcenter message.                                    *
 ***************************************************************/
int ShowTCMessage(int DebugMode, /* I: In debug mode view it */
char *ToSprintf, /* I: Sprintf this */
int UseSprintf, /* I: Use sprintf */
char *AddToSprintf) /* I: Sprintf this */
{
	char Tc_message[256];
	char Tc_message2[256];

	STR_INIT(Tc_message);

	if (DebugMode == 0)
		return (0);

	if (ToSprintf == NULL)
		StrCpy(Tc_message, 256, "NULL");
	else
		StrCpy(Tc_message, 256, ToSprintf);

	printf("%s", "  ");
	printf("%s", ": ");
	printf("%s", Tc_message);

	if (UseSprintf == 1) {
		printf("%s", " [");
		printf("%s", AddToSprintf);
		printf("%s", "]");
	}

	printf("%s", "\n");

	return (1);
}
