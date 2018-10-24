extern "C"
{
#include <wlr/types/wlr_idle.h>
}

#include "plugin.hpp"
#include "output.hpp"
#include "core.hpp"
#include "config.hpp"

class wayfire_idle_inhibit : public wayfire_plugin_t
{
    bool enabled = true;
    activator_callback toggle;

    void init(wayfire_config *config)
    {
        auto binding = config->get_section("idle-inhibit")->get_option("toggle", "<super> <shift> KEY_I");

        toggle = [=] ()
        {
            enabled = !enabled;
            wlr_idle_set_enabled(core->protocols.idle, NULL, enabled);
        };

        output->add_activator(binding, &toggle);
    }

    void fini()
    {
        if (!enabled) // enable idle if the plugin is disabled
            toggle();

        output->rem_binding(&toggle);
    }
};

extern "C"
{
    wayfire_plugin_t *newInstance()
    {
        return new wayfire_idle_inhibit;
    }
}
