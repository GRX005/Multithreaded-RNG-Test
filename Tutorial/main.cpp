#include <iostream>
#include <random>
#include <thread>
#include <chrono>
#include <Windows.h>

using namespace std;
thread_local mt19937_64 gen(random_device{}());
void genAAn(vector<long long>& local_v, uniform_int_distribution<long long> intDistr3);
void CLI();
bool bCLI = true;
unsigned long long y;
unsigned long long z;

int main() {
#if 0
	int a[5];
	a[0] = 1;
	a[1] = 23;
	cout << a[0] + a[1] << endl;
	setlocale(LC_ALL, "hun");
	string őű = "asdáéőúűöüó";
	cout << őű;
#endif // 0
#if 0
	int a[5];
	for (int i = 0; i < 5; i++) {
		cout << "Add meg az " << i + 1 << ". számot!" << endl;
		cin >> a[i];
	}
	cout << endl;
	for (int i = 0; i < 5; i++) {
		cout << i + 1 << ". elem: " << a[i] << endl;
	}
#endif // 0
	vector<thread> threads;
	vector<long long> v;

	cout << "How many numbers do you want to generate?" << endl;
	cin >> y;
	cout << "Give an interval. (Ex: -10000:10000)" << endl;
	string in;
	cin >> in;
	const size_t dP = in.find(':');

	const long long in1 = stoll(in.substr(0, dP));
	const long long in2 = stoll(in.substr(dP+1));

	thread_local uniform_int_distribution<long long> intDistr(in1, in2);

	cout << "How many threads do you want to use?" << endl;
	int th;
	cin >> th;

	auto start = chrono::steady_clock::now();
	z = y/th;
	const unsigned long long x = y / z;
	vector<vector<long long>> results(x);
	for (unsigned long long i = 0; i < x; i++) {
		threads.push_back(thread(genAAn, ref(results[i]), ref(intDistr)));
		cout << "New generator thread initialized.\n";
	}
	thread cliThread(CLI);
	for (thread &t : threads) {
		t.join();
	}
	for (size_t i = 0; i < y % th; i++) {
		results[0].push_back(intDistr(gen));
	}
	for (const auto& local_v : results) {
		v.insert(v.end(), local_v.begin(), local_v.end());
	}
	bCLI = false;
	cliThread.join();
	auto end = chrono::steady_clock::now();
	cout << "Time passed: " << chrono::duration_cast<chrono::milliseconds>(end - start) << endl;
	cout << "Vector size: " << v.size() << endl;
	cout << "Do you want to see all generated numbers? [Y/N] ";
	char c;
	cin >> c;
	c=tolower(c);
	if (c == 'y') {
		for (size_t i = 0; i < v.size(); i++) {
			cout << "Number " << i + 1 << ": " << v[i] << endl;
		}
	}
	system("pause");
	return 0;
} 

void genAAn(vector<long long>& local_v, uniform_int_distribution<long long> intDistr) {
	for (size_t i = 0; i < z; i++)
	{
		//lock_guard<mutex> lock(mtx);
		local_v.push_back(intDistr(gen));
	}
}

void CLI() {
	const string b = "Generating";
	const string c = ".";
	const string a = string(13, ' ') + "\r";
	int i = 0;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ci;
	GetConsoleCursorInfo(h, &ci);
	ci.bVisible = 0;
	SetConsoleCursorInfo(h, &ci);

	while (bCLI)
	{
		switch (i)
		{
		case 0:
			cout << a+b;
			i++;
			break;
		case 1:
			cout << b + c;
			i++;
			break;
		case 2:
			cout << b + c + c;
			i++;
			break;
		case 3:
			cout << b + c + c + c;
			i = 0;
			break;
		default:
			break;
		}
		cout << "\r";
		this_thread::sleep_for(chrono::milliseconds(500));
	}
	cout << a;
	ci.bVisible = 1;
	SetConsoleCursorInfo(h, &ci);
}