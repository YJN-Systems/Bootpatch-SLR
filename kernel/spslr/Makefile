obj-$(CONFIG_SPSLR) += spslr.o spslr_env.o spslr_randomizer.o
obj-$(CONFIG_SANEMAKER) += sanemaker_traps.o

CFLAGS_REMOVE_spslr.o += $(PINPOINT_PLUGIN_CFLAGS)
CFLAGS_REMOVE_spslr_env.o += $(PINPOINT_PLUGIN_CFLAGS)
CFLAGS_REMOVE_spslr_randomizer.o += $(PINPOINT_PLUGIN_CFLAGS)
CFLAGS_REMOVE_sanemaker_traps.o += $(PINPOINT_PLUGIN_CFLAGS)
