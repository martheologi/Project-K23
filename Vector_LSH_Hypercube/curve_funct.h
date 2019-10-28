Curve Initialize_Curve(string line, double* max_coord);

int Initialize_Curve_Dataset(string filename, vector<Curve>* Curves_dataset, int* max_points, double* max_coord);

double point_distance(Point x, Point y);

double minimum(double t1, double t2, double t3);

void a1_a2(double* a1, double* a2, Point t, Point point, double delta);

double** DTW(Curve p, Curve q);

void print_table(double** table, int m1, int m2);

Curve curve_ExactNN(vector<Curve> Curves_dataset, Curve curve, int c, double* ExactNN_dist);
