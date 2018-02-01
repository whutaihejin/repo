#include <thread>
#include <memory>
#include <unistd.h>
#include <iostream>

void Task(int val, const std::string& msg) {
  std::cout << val << " " << msg << std::endl;
}

void Bad() {
  char buffer[1024] = {0};
  sprintf(buffer, "%i", 111);
  std::thread thread(Task, 3, buffer);
  thread.detach();
}

void Good() {
  char buffer[1024] = {0};
  sprintf(buffer, "%i", 222);
  std::thread thread(Task, 3, std::string(buffer));
  thread.join();
}

void Work(int val, std::string& msg) {
  std::cout << val << " " << msg << std::endl;
  msg = "modified";
}

struct Data {
  int lng;
  int lat;
};

// void Fun(const Data& d) {
void Fun(Data& d) {
  d.lng = 11;
  d.lat = 22;
  std::cout << d.lng << " " << d.lat << std::endl;
}

class DoTask {
public:
  DoTask(): val_(999) {}

  void Display() {
    std::cout << "display " <<  val_ << std::endl;
  }
private:
  int val_;
};

void MoveTask(std::unique_ptr<Data> p) {
  std::cout << p->lng << " " << p->lat << std::endl;
}

int main() {
  std::thread thread(Task, 3, "hello");
  thread.join();
  //
  Bad();
  sleep(1);

  //
  Good();
  
  //
  std::string msg = "hello";
  // std::thread work(Work, 3, buffer);
  std::thread xx(Work, 3, std::ref(msg));
  xx.join();
  std::cout << "main thread " << msg << std::endl;

  //
  Data d = {0, 0};
  std::thread t(Fun, std::ref(d));
  t.join();
  std::cout << d.lng << " " << d.lat << std::endl;

  //
  DoTask do_task;
  std::thread t2(&DoTask::Display, &do_task);
  t2.join();

  //
  std::unique_ptr<Data> p(new Data{88, 88});
  // std::thread t3(MoveTask, p);
  std::thread t3(MoveTask, std::move(p));
  t3.join();
  std::cout << (p == NULL ? "true" : "false") << std::endl;
  return 0;
}
