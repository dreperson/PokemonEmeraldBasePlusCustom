#include "global.h"
#include "event_data.h"   // VarGet/VarSet
#include "constants/vars.h"   // VAR_LEVEL_CAP (if needed)
#include "constants/flags.h"  // FLAG_DEFEATED_...
#include "item.h"              // CheckBagHasItem, AddBagItem
#include "constants/items.h"   // ITEM_*
#include "pokemon.h"
#include "constants/species.h"
#include "coins.h"
#include "money.h"
#include "string_util.h"
#include "constants/coins.h"

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

void FindPartyFeebas(void)
{
    u8 i;

    gSpecialVar_Result = FALSE;
    for (i = 0; i < gPlayerPartyCount && i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES_OR_EGG) == SPECIES_FEEBAS)
        {
            gSpecialVar_0x8004 = i;
            gSpecialVar_Result = TRUE;
            return;
        }
    }
}

void MaxPartyFeebasBeauty(void)
{
    u8 beauty = 255;
    u16 i = gSpecialVar_0x8004;

    if (i < gPlayerPartyCount && i < PARTY_SIZE
     && GetMonData(&gPlayerParty[i], MON_DATA_SPECIES_OR_EGG) == SPECIES_FEEBAS)
        SetMonData(&gPlayerParty[i], MON_DATA_BEAUTY, &beauty);
}

// Result: 0 = valid, 1 = not enough coin space, 2 = not enough money.
static u16 CheckChosenCoinPurchase(u16 count)
{
    if (count > MAX_COINS - GetCoins())
        return 1;
    if (!IsEnoughMoney(&gSaveBlock1Ptr->money, (u32)count * 20))
        return 2;
    return 0;
}

static u16 ChosenCoinCount(void)
{
    return gSpecialVar_0x8004 * 1000 + gSpecialVar_0x8005 * 100
         + gSpecialVar_0x8006 * 10 + gSpecialVar_0x8007;
}

void QuoteCoinPurchase(void)
{
    u16 count = ChosenCoinCount();
    gSpecialVar_Result = count == 0 ? 3 : CheckChosenCoinPurchase(count);
    ConvertIntToDecimalStringN(gStringVar1, count, STR_CONV_MODE_LEFT_ALIGN, 4);
    ConvertIntToDecimalStringN(gStringVar2, (u32)count * 20, STR_CONV_MODE_LEFT_ALIGN, 6);
}

void BuyChosenCoins(void)
{
    u16 count = ChosenCoinCount();
    gSpecialVar_Result = CheckChosenCoinPurchase(count);
    if (gSpecialVar_Result == 0 && count != 0)
    {
        RemoveMoney(&gSaveBlock1Ptr->money, (u32)count * 20);
        AddCoins(count);
    }
}
