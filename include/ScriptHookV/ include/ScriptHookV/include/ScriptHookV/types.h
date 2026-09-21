
/* scripts */

IMPORT void scriptWait(DWORD time);
IMPORT void scriptRegister(HMODULE module, void(*LP_SCRIPT_MAIN)());
IMPORT void scriptRegisterAdditionalThread(HMODULE module, void(*LP_SCRIPT_MAIN)());
IMPORT void scriptUnregister(HMODULE module);
IMPORT void scriptUnregister(void(*LP_SCRIPT_MAIN)()); // deprecated

IMPORT void nativeInit(UINT64 hash);
IMPORT void nativePush64(UINT64 val);
IMPORT PUINT64 nativeCall();

static void WAIT(DWORD time) { scriptWait(time); }
static void TERMINATE() { WAIT(MAXDWORD); }

// Returns pointer to global variable
// make sure that you check game version before accessing globals because
// ids may differ between patches
IMPORT UINT64 *getGlobalPtr(int globalId);

/* world */

// Get entities from internal pools
// return value represents filled array elements count
// can be called only in the same thread as natives
IMPORT int worldGetAllVehicles(int *arr, int arrSize);
IMPORT int worldGetAllPeds(int *arr, int arrSize);
IMPORT int worldGetAllObjects(int *arr, int arrSize);
IMPORT int worldGetAllPickups(int *arr, int arrSize);

/* misc */

// Returns base object pointer using it's script handle
// make sure that you check game version before accessing object fields because
// offsets may differ between patches
IMPORT BYTE *getScriptHandleBaseAddress(int handle);

enum eGameVersion : int
{
	VER_1_0_335_2_STEAM,
	VER_1_0_335_2_NOSTEAM,

	VER_1_0_350_1_STEAM,
	VER_1_0_350_2_NOSTEAM,

	VER_1_0_372_2_STEAM,
	VER_1_0_372_2_NOSTEAM,

	VER_1_0_393_2_STEAM,
	VER_1_0_393_2_NOSTEAM,

	VER_1_0_393_4_STEAM,
	VER_1_0_393_4_NOSTEAM,

	VER_1_0_463_1_STEAM,
	VER_1_0_463_1_NOSTEAM,

	VER_1_0_505_2_STEAM,
	VER_1_0_505_2_NOSTEAM,

	VER_1_0_573_1_STEAM,
	VER_1_0_573_1_NOSTEAM,

	VER_1_0_617_1_STEAM,
	VER_1_0_617_1_NOSTEAM,

	VER_SIZE,
	VER_UNK = 
IMPORT eGameVersion getGameVersion();
