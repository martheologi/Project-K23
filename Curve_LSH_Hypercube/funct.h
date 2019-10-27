Curve Initialize_Curve(string line);

int Initialize_Curve_Dataset(string, vector<Curve>*);

double minimum(double t1, double t2, double t3);

double** DTW(Curve p, Curve q);

void print_table(double** table, int m1, int m2);
