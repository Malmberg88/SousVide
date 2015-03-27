class Menu{
public:
	Menu();
	~Menu();
	void change();
	void interact();
	string print_horz();
	string print_vert();
	enum class VERT{Menu = 1,
					Temp = 2,
					Param = 3};

private:
	unsigned int horz_menu_layer;
	unsigned int vert_menu_layer;
}