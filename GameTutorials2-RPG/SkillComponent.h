#pragma once
class Skill
{
public:
	Skill() : exp(0), expNext(100), level(1), levelCap(99)
	{

	};
	Skill(int exp, int level, int level_cap, int exp_next)
		: exp(exp), level(level), levelCap(level_cap), expNext(exp_next)
	{

	};

	//Accessors
	inline const int& getLevel() const { return level; };
	inline const int& getLevelCap() const { return levelCap; };
	inline const int& getExp() const { return exp; };
	inline const int& getExpNext() const { return expNext; };

	//Setters
	void setLevel(const int level) { this->level = level; };
	void setLevelCap(const int level_cap) { levelCap = level_cap; };
	void setExp(const int exp) { this->exp = exp; };
	void setExpNext(const int exp_next) { expNext = exp_next; };

	//Functions
	void addExp(const int exp)
	{
		if (level < levelCap) {
			this->exp += exp;
			updateLevel(true);
		}
	};
	void loseExp(const int exp)
	{
		if (level > 0) {
			this->exp += exp;
			updateLevel(false);
		}
	};

	void updateLevel(bool up) {
		if (up) {
			while (exp >= expNext) {
				if (level < levelCap) {
					level++;
					expNext = 2 * static_cast<int>(static_cast<int>(pow(level, 3)) - 6 * static_cast<int>(pow(level, 2)) + (level * 17) - 12);
				}
				else {
					expNext += exp + 1; //will kick out of while loop and should never enter again
				}
			}
		}
		else {
			while (exp >= 0) {
				if (level > 0) {
					level--;
					expNext = 100 + (level, 2) + (level * 12);
				}
			}
		}
	}

	//variables
	int exp;
	int expNext;
	int level;
	int levelCap;
};

class SkillComponent
{
public:
	SkillComponent();

	//Functions
	Skill& getSkill(std::string key);
	const int& getSkillLvl(std::string key) const;
	void setSkill(std::string key, const int level, const int levelCap, const int exp, const int expNext);

	void addExp(std::string key, const int exp);
	void loseExp(std::string key, const int exp);

private:
	std::map<std::string, Skill> skills;
};

