#include "global.h"
#include "event_data.h"   // VarGet/VarSet
#include "constants/vars.h"   // VAR_LEVEL_CAP (if needed)
#include "constants/flags.h"  // FLAG_DEFEATED_...
#include "item.h"              // CheckBagHasItem, AddBagItem
#include "constants/items.h"   // ITEM_*

void EVsNo(void)
{
	gSaveBlock2Ptr->determineEVs = 1;
}

void EVsYes(void)
{
	gSaveBlock2Ptr->determineEVs = 0;
}

void TMsNo(void)
{
	gSaveBlock2Ptr->determineTMs = 0;
}

void TMsYes(void)
{
	gSaveBlock2Ptr->determineTMs = 1;
}

void BERsNo(void)
{
	gSaveBlock2Ptr->determineBERs = 0;
}

void BERsYes(void)
{
	gSaveBlock2Ptr->determineBERs = 1;
}

void BasePlusItems(void)
{
	VarSet(VAR_RESULT, 1);

	if (!CheckBagHasItem(ITEM_PORTA_PC, 1))
	{
		VarSet(VAR_RESULT, 0);
		AddBagItem(ITEM_PORTA_PC, 1);
	}
	if (!CheckBagHasItem(ITEM_MEDICINE, 1))
	{
		VarSet(VAR_RESULT, 0);
		AddBagItem(ITEM_MEDICINE, 1);
	}
	if (!CheckBagHasItem(ITEM_ENDLESS_CANDY, 1))
	{
		VarSet(VAR_RESULT, 0);
		AddBagItem(ITEM_ENDLESS_CANDY, 1);
	}
	if (!CheckBagHasItem(ITEM_ENDLESS_REPEL, 1))
	{
		VarSet(VAR_RESULT, 0);
		AddBagItem(ITEM_ENDLESS_REPEL, 1);
	}
	if (!CheckBagHasItem(ITEM_STATUS_CASE, 1))
	{
		VarSet(VAR_RESULT, 0);
		AddBagItem(ITEM_STATUS_CASE, 1);
	}

	if (!CheckBagHasItem(ITEM_LINK_CABLE, 1))
	{
		VarSet(VAR_RESULT, 0);
		AddBagItem(ITEM_LINK_CABLE, 1);
	}

}