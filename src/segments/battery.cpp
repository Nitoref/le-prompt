// #include <CoreFoundation/CoreFoundation.h>
// #include <IOKit/ps/IOPowerSources.h>
// #include <IOKit/ps/IOPSKeys.h>


// int BatteryAC::GetBatteryPercent(int *piBatteryPercent)
// {

// 	CFTypeRef blob = IOPSCopyPowerSourcesInfo();
// 	CFArrayRef sources = IOPSCopyPowerSourcesList(blob);
	
// 	CFDictionaryRef pSource = NULL;
// 	const void *psValue;
	
// 	if (CFArrayGetCount(sources) == 0)
// 		return 0;	// Could not retrieve battery information.  System may not have a battery.

// 	pSource = IOPSGetPowerSourceDescription(blob, CFArrayGetValueAtIndex(sources, i));
// 	psValue = (CFStringRef)CFDictionaryGetValue(pSource, CFSTR(kIOPSNameKey));
	
// 	int curCapacity = 0;
// 	int maxCapacity = 0;
// 	int percent;
	
// 	psValue = CFDictionaryGetValue(pSource, CFSTR(kIOPSCurrentCapacityKey));
// 	CFNumberGetValue((CFNumberRef)psValue, kCFNumberSInt32Type, &curCapacity);
	
// 	psValue = CFDictionaryGetValue(pSource, CFSTR(kIOPSMaxCapacityKey));
// 	CFNumberGetValue((CFNumberRef)psValue, kCFNumberSInt32Type, &maxCapacity);
	
// 	*piBatteryPercent = (int)((double)curCapacity/(double)maxCapacity * 100);
	
// 	if (piBatteryPercent < 0 || piBatteryPercent > 100)
// 		return -1;	// Could not retrieve the battery information
// 	else
// 		return 1;	// Success
// }
