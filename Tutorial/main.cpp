#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;
mt19937_64 gen(random_device{}());
uniform_int_distribution<> intDistr(1, 1000);
void genAAn(vector<unsigned long long>& local_v);
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
	auto start = chrono::steady_clock::now();
	z = y/2;
	unsigned long long x = y / z;
	vector<vector<unsigned long long>> results(x);
	for (unsigned long long i = 0; i < x; i++) {
		threads.push_back(thread(genAAn, ref(results[i])));
		cout << "new thread\n";
	}
	for (thread &t : threads) {
		t.join();
	}
	if (y % 2 != 0) {
		results[0].push_back(intDistr(gen));
	}
	for (const auto& local_v : results) {
		v.insert(v.end(), local_v.begin(), local_v.end());
	}
	auto end = chrono::steady_clock::now();
	cout << "\nTime passed: " << chrono::duration_cast<chrono::milliseconds>(end - start) << endl;
	cout << "Vector size: " << v.size() << endl;
	for (size_t i = 0; i < v.size(); i++) {
		cout << "Number " << i + 1 << ": " << v[i] << endl;
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