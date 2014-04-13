#include "storm.h"

// Lock specifications
#define UNLOCKED 0

typedef unsigned long ULONG_PTR;
typedef ULONG_PTR KSPIN_LOCK;
typedef KSPIN_LOCK *PKSPIN_LOCK;

void InitializeSpinLock(PKSPIN_LOCK SpinLock) {
  __hv_updates_resource("LOCK", SpinLock, UNLOCKED);
}

void AcquireSpinLock(PKSPIN_LOCK SpinLock) {
  int tid = storm_getThreadID();
  int lockStatus;
  STORM_ATOMIC(
    __hv_assume(__resource("LOCK", SpinLock) == lockStatus);
    STORM_ASSERT(tid != lockStatus);
    __hv_assume(lockStatus == UNLOCKED);
    __hv_updates_resource("LOCK", SpinLock, tid);
  );
}

void ReleaseSpinLock(PKSPIN_LOCK  SpinLock) {
  int lockStatus;
  STORM_ATOMIC(
    __hv_assume(__resource("LOCK", SpinLock) == lockStatus);
    STORM_ASSERT(lockStatus == storm_getThreadID());
    __hv_updates_resource("LOCK", SpinLock, UNLOCKED);
  );
}

