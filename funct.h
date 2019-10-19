Vector_Item get_item(string);

int Initialize_Dataset_Vector(string, vector<Vector_Item>*);

Vector_Item AproximateNN(vector<Vector_Item>, Vector_Item, vector<unordered_multimap<int, int>>, int, int, int, long int, int, int);

Vector_Item ExactNN(vector<Vector_Item>, Vector_Item, int);

void write_results(string, string, string, double, double, double, double);
