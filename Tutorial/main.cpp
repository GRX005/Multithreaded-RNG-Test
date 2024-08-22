#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <chrono>

using namespace std;
mt19937_64 gen(random_device{}());
uniform_int_distribution<> intDistr(1, 100000);
void genAAn(vector<unsigned long long>& local_v);
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
	vector<unsigned long long> v;

	cout << "How many numbers do you want to generate?" << endl;
	cin >> y;
	cout << "In what range? (Ex: 1-10000)" << endl;

	auto start = chrono::steady_clock::now();
	z = y/2;
	unsigned long long x = y / z;
	vector<vector<unsigned long long>> results(x);
	for (unsigned long long i = 0; i < x; i++) {
		threads.push_back(thread(genAAn, ref(results[i])));
		cout << "New generator thread initialized.\n";
	}
	thread cliThread(CLI);
	for (thread &t : threads) {
		t.join();
	}
	if (y % 2 != 0) {
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
	if (c == 'Y') {
		for (size_t i = 0; i < v.size(); i++) {
			cout << "Number " << i + 1 << ": " << v[i] << endl;
		}
	}
	return 0;
} 

void genAAn(vector<unsigned long long>& local_v) {
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
	while (bCLI)
	{
		switch (i)
		{
		case 0:
			cout << a;
			cout << b + c;
			i++;
			break;
		case 1:
			cout << b + c + c;
			i++;
			break;
		case 2:
			cout << b+c+c+c;
			i = 0;
			break;
		default:
			break;
		}
		cout << "\r";
		this_thread::sleep_for(chrono::milliseconds(500));
	}
	cout << a;
}