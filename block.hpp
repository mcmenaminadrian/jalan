virtual class Block
{
	private:
		Block *prev;
		Block *next;
		int start;
		int length;

	public:
	Block();
	~Block();
	virtual Block* grow(int point, int width);
	virtual void setNext(block *ptr);
	virtual void setPrev(block *ptr);
	void setStart(int point);
	void setLength(int width);
	virtual block *getNext() const;
	virtual block *getPrev() const;
	int getStart() const;
	int getLength() const; 	
}

class Instruction: public Block
{
	Instruction(): Block(){};
}

		
