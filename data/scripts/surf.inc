EventScript_UseSurf::
	lockall
	setfieldeffectargument 0, 0  @ Badge-based Surf uses the lead Pokemon.
	dofieldeffect FLDEFF_USE_SURF
EventScript_ReleaseUseSurf::
	releaseall
EventScript_EndUseSurf::
	end
