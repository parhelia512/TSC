#include "../../../enemies/spika.h"
#include "../../../level/level.h"
#include "../../../core/sprite_manager.h"
#include "../../../core/property_helper.h"
#include "mrb_enemy.h"
#include "mrb_spika.h"

/**
 * Class: Spika
 *
 * Parent: [Enemy](enemy.html)
 * {: .superclass}
 *
 * _Spikas_ are big, rolling balls armed with spikes. They follow
 * Maryo and try to overroll him. Big spikas tend to block paths,
 * so you somehow need to make them move away. The default spika
 * is not resistant to fire or ice, so you may want to change
 * that using the apropriate methods from the `Enemy` class.
 */

using namespace SMC;
using namespace SMC::Scripting;

// Extern
struct RClass* SMC::Scripting::p_rcSpika = NULL;

/**
 * Method: Spika::new
 *
 *   new() → a_spika
 *
 * Create a new spika enemy with the default values.
 */
static mrb_value Initialize(mrb_state* p_state,  mrb_value self)
{
	cSpika* p_spika = new cSpika(pActive_Level->m_sprite_manager);
	DATA_PTR(self) = p_spika;
	DATA_TYPE(self) = &rtSMC_Scriptable;

	// This is a generated object
	p_spika->Set_Spawned(true);

	// Let SMC manage the memory
	pActive_Level->m_sprite_manager->Add(p_spika);

	return self;
}

/**
 * Method: Spika#color=
 *
 *   color= ( color ) → color
 *
 * Specifies the color/type of this spika.
 *
 * #### Parameters
 * color
 * : The spika’s new color. One of the following symbols:
 *   `:orange`, `:green`, `:grey`, `:red`.
 */
static mrb_value Set_Color(mrb_state* p_state, mrb_value self)
{
	mrb_sym color;
	mrb_get_args(p_state, "n", &color);
	std::string colorstr(mrb_sym2name(p_state, color));

	DefaultColor col;
	if (colorstr == "orange")
		col = COL_ORANGE;
	else if (colorstr == "green")
		col = COL_GREEN;
	else if (colorstr == "grey")
		col = COL_GREY;
	else if (colorstr == "red")
		col = COL_RED;
	else {
		mrb_raisef(p_state, MRB_ARGUMENT_ERROR(p_state), "Invalid spika color %s", colorstr.c_str());
		return mrb_nil_value(); // Not reached
	}

	cSpika* p_spika = Get_Data_Ptr<cSpika>(p_state, self);
	p_spika->Set_Color(col);

	return mrb_symbol_value(color);
}

/**
 * Method: Spika#color
 *
 *   color() → a_symbol
 *
 * Returns the spika’s current color. See #color= for
 * possible return values.
 */
static mrb_value Get_Color(mrb_state* p_state, mrb_value self)
{
	cSpika* p_spika = Get_Data_Ptr<cSpika>(p_state, self);
	switch(p_spika->m_color_type) {
	case COL_ORANGE:
		return str2sym(p_state, "orange");
	case COL_GREEN:
		return str2sym(p_state, "green");
	case COL_GREY:
		return str2sym(p_state, "grey");
	default:
		return mrb_nil_value();
	}
}

/**
 * Method: Spika#speed=
 *
 *   speed=( speed ) → speed
 *
 * Specify the spika’s speed. The default speed values are
 * as follows:
 *
 * | Spika color | Spika default speed |
 * |:-----------:|:-------------------:|
 * | orange      | 3.0                 |
 * | green       | 4.0                 |
 * | grey        | 7.0                 |
 * | red         | 10.0                |
 *
 * #### Parameters
 * speed
 * : The spika’s new speed. A float.
 */
static mrb_value Set_Speed(mrb_state* p_state, mrb_value self)
{
	mrb_float speed;
	mrb_get_args(p_state, "f", &speed);

	if (speed < 0) {
		mrb_raise(p_state, MRB_RANGE_ERROR(p_state), "Spika speed must be >= 0");
		return mrb_nil_value(); // Not reached
	}

	cSpika* p_spika = Get_Data_Ptr<cSpika>(p_state, self);
	p_spika->m_speed = speed;

	return mrb_float_value(p_state, speed);
}

/**
 * Method: Spika#speed
 *
 *   speed() → a_float
 *
 * Returns the spika’s speed, a float.
 */
static mrb_value Get_Speed(mrb_state* p_state, mrb_value self)
{
	cSpika* p_spika = Get_Data_Ptr<cSpika>(p_state, self);
	return mrb_float_value(p_state, p_spika->m_speed);
}

void SMC::Scripting::Init_Spika(mrb_state* p_state)
{
	p_rcSpika = mrb_define_class(p_state, "Spika", p_rcEnemy);
	MRB_SET_INSTANCE_TT(p_rcSpika, MRB_TT_DATA);

	mrb_define_method(p_state, p_rcSpika, "initialize", Initialize, MRB_ARGS_NONE());
	mrb_define_method(p_state, p_rcSpika, "color=", Set_Color, MRB_ARGS_REQ(1));
	mrb_define_method(p_state, p_rcSpika, "color", Get_Color, MRB_ARGS_NONE());
	mrb_define_method(p_state, p_rcSpika, "speed=", Set_Speed, MRB_ARGS_REQ(1));
	mrb_define_method(p_state, p_rcSpika, "speed", Get_Speed, MRB_ARGS_NONE());
}
