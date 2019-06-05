template <typename elemType> class ListItem;
template <typename elemType> class List {
public:
    List<elemType>();
    List<elemType>(const List<elemType>&);
    List<elemType>& operator=(const List<elemType>&);
    ~List();
    // ListIterm requires template argument
    void insert(ListItem<elemType> *ptr, elemType value);
private:
    ListItem<elemType> *front, *end;
};
