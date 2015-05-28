#include "SkillMagicSpell.h"

SkillMagicSpell::SkillMagicSpell(string spell, int frame)
{
	this->_spell = spell;
	this->_send_frame = frame;
}
int SkillMagicSpell::getSendFrame() {
	return this->_send_frame;
}
string SkillMagicSpell::getSpell() {
	return this->_spell;
}