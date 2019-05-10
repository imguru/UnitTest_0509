struct User {
	virtual ~User() {}

	virtual void Stop() = 0;
	virtual void Say(const std::string& message) = 0;
	virtual void Attack(User *target) = 0;
	virtual void Move(int x, int y) = 0;
	virtual int GetX() const = 0;
	virtual int GetY() const = 0;
};
