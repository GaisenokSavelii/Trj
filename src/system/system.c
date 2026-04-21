#include <Windows.h>

wchar_t *switch_cpu_architecture(SYSTEM_INFO system_info) {
  switch (system_info.wProcessorArchitecture) {
  case PROCESSOR_ARCHITECTURE_AMD64: {
    return L"x64";
    break;
  }
  case PROCESSOR_ARCHITECTURE_ARM: {
    return L"ARM";
    break;
  }
  case PROCESSOR_ARCHITECTURE_ARM64: {
    return L"ARM64";
    break;
  }
  case PROCESSOR_ARCHITECTURE_IA64: {
    return L"Intel Itanium-based";
    break;
  }
  case PROCESSOR_ARCHITECTURE_INTEL: {
    return L"x86";
    break;
  }
  case PROCESSOR_ARCHITECTURE_UNKNOWN: {
    return L"Unknown architecture.";
    break;
  }
  }

  return NULL;
}

SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX *get_logical_processors_info() {
  DWORD size = 0;

  GetLogicalProcessorInformationEx(RelationAll, NULL, &size);

  SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX *info =
      (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX)malloc(size);

  GetLogicalProcessorInformationEx(RelationAll, info, &size);

  return info;
}