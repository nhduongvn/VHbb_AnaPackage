#include "inc/AnaBaseSelector.h"
#include "TList.h"

void    AnaBaseSelector::SlaveBegin(const BaseTree* r) {};
void    AnaBaseSelector::Process(const BaseTree* r) {};
void    AnaBaseSelector::SlaveTerminate(const BaseTree* r) {};
void    AnaBaseSelector::Terminate(TList* mergedList) {};
