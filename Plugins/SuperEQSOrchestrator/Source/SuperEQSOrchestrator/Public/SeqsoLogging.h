#pragma once
/**
 * Summary: Central logging categories and helpers for Super-EQSOrchestrator.
 * Usage: Include in implementation files to log under specific domains.
 * Thread-safety: Engine logging is thread-safe; categories are static.
 * Errors/Logs: N/A.
 * Performance: Prefer Display/Log; forbid VeryVerbose in Shipping (see AGENTS §LOGGING).
 */

#pragma region Includes
#include "Logging/LogMacros.h"
#pragma endregion Includes

#pragma region LogCategories
DECLARE_LOG_CATEGORY_EXTERN(LogSEQSO_Query, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogSEQSO_Budget, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogSEQSO_Collision, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogSEQSO_Orchestrator, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(LogSEQSO_Perf, Log, All);
#pragma endregion LogCategories

