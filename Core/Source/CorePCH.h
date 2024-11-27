#pragma once

// This header comes with "Core/Log.h" as well, no need to re-include or pre-include in this PCH.
#include "Core/Assert.h"

#ifdef HS_PLATFORM_WINDOWS
	#include <Windows.h>
#elif defined HS_PLATFORM_LINUX
	#include <linux/limits.h>
	#include <unistd.h>
#endif

#include <unordered_map>
#include <unordered_set>
#include <string_view>
#include <filesystem>
#include <functional>
#include <optional>
#include <iostream>
#include <fstream>
#include <sstream>
#include <variant>
#include <thread>
#include <atomic>
#include <memory>
#include <string>
#include <vector>
#include <bitset>
#include <chrono>
#include <random>
#include <limits>
#include <array>
#include <stack>
#include <queue>
#include <deque>
#include <mutex>
#include <regex>
#include <map>
#include <set>
#include <any>
#include <new>
