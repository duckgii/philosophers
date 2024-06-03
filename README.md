# philosophers
***
- 42 3서클 과제  [https://cdn.intra.42.fr/pdf/pdf/115372/en.subject.pdf]

## 문제 설명   
1. 한 명 이상의 철학자가 둥근 테이블에 둘러 앉아있고, 각자 포크를 하나씩 가지고 있다.  
2. 그들은 반복적으로 먹고, 생각하고, 잔다. 동시에 두 개 이상의 행위는 불가능하다.  
3. 그들은 양 손에 포크를 하나씩 쥐고 있어야 식사를 할 수 있다.  
4. 식사를 마치면 포크를 내려놓고, 잠을 자기 시작한다.  
5. 일어나면 다시 생각하기를 반복한다. 시뮬레이션은 그들이 아사할 때 중단된다.  
6. 철학자들 끼리는 소통할 수 없고, 모두가 굶어선 안 된다.  

### Mandatiry Part  
1. 각각의 철학자들은 스레드로 구현되어야 한다.
2. 한 쌍의 철학자 사이에는 하나의 포크가 존재하고, 한 명의 철학자만 있는 경우에는 하나의 포크만 존재한다.
3. mutex를 이용하여 포크 복사를 방지해라.

### Bonus Part
1. 모든 포크는 테이블 중앙에 위치한다.
2. 사용할 수 있는 포크 정보는 samaphore에 의해 표현된다.
3. 각각의 철학자들은 프로세스로 구현된다. 하지만 부모 프로세스는 철학자가 아니다.

## 필요한 개념
1. Data Race
  - Race condition : 현재 작업이 제어할 수 없는 또다른 작업과의 진행 순서, 즉 타이밍에 따라 결과가 달라져 여러 결과를 만들어낼 수 있는 바람직하지 않은 상황
  - Data race : 다른 곳에서 읽을 가능성이 있는 어떤 메모리 위치에 쓰기 작업을 하는 것, 특히 그것이 위험한 상황
  - data race는 race condition의 부분집합이다.
  - Data Race는 2개 이상의 다른 스레드가 동시성을 통해 같은 데이터에 접근하고 그 중 하나 이상이 값을 수정하는 경우 일어날 수 있다.
    
2. 스레드
  - 프로세스 내에서 실제로 작업을 수행하는 주체. 모든 프로세느는 한 개 이상의 스레드가 존재하여 작업을 수행
  - 두 개 이상의 스레드를 가지는 프로세스를 멀티스레드 프로세스라고 한다.
  - 프로세스 : 실행중인 프로그램. 운영체제에 의해 메모리 공간을 할당받아 실행중인 것

3. mutex
  - 공유된 자원의 데이터 혹은 임계영역 등에 하나의 프로세스 또는 스레드가 접근하는 것을 막아줌(대상이 하나)
  - 임계구역을 가진 스레드들의 실행시간이 서로 겹치지 않고 각각 단독으로 실행되도록 하는 기술입니다.
  - key를 기반으로 한 상호배제 기법으로 key에 해당하는 어떤 객제가 있는데 이 객체를 소유한 스레드/프로세스만이 공유자원에 접근 가능
  - 동기화 또는 락을 사용함으로써 뮤텍스 객체를 두 스레드가 동시에 사용할 수 없다.

4. samaphore
  - 공유된 자원의 데이터 혹은 임계영역 등에 하나의 프로세스 또는 스레드가 접근하는 것을 막아줌(대상이 하나 이상)
  - 공유 자원에 접근할 수 있는 프로세스의 최대 허용치만큼 동시에 사용자가 접근할 수 있으며, 각 프로세스는 세마포어의 값을 확인하고 변경할 수 있다.

***
## 구현 방식
### 1. Mandatory
1 .인원수만큼 스레드를 만들고 각각 초기화한 철학자 구조체를 넘겨준다.  
2. 각각의 스레드는 열심히 먹으면서 카운트를 증가시키고(모니터링 스레드나 다른 스레드가 접근하는 데이터 확인하거나 접근할 때는 mutex걸어준다), 굶어 죽는다면 flag를 변경한다.  
3. 모니터링 스레드는 계속해서 동작하면서 누구 하나가 죽거나, 다 최소 먹어야하는 양만큼 먹는다면 순서대로 모두 죽인다.  

-> 수정  
1. 필로소퍼 구조체를 만들기 전에 정보를 담고 있는 info구조체를 먼저 만든다.    
2. info 뮤텍스, 철학자의 생존 정보, 식사 횟수 최소 조건을 충족하지 못한 철학자 수를 필수 요소로 넣는다.  
3. info 구조체를 각 철학자가 들고다니게 한다.  
4. 각 철학자는 스레드를 생성하여 생각하고 먹고 자기를 반복하는데 굶어 죽는다면 info 구조체의 생존 정보를 변경하여 모든 스레드의 동작을 멈춘다.  
5. 각 스레드의 최소 식사 횟수를 채우면 info 구조체의 값을 변경한다.  
6. info 구조체의 정보에 접근할 때는 무조건 뮤텍스를 걸어야 한다.  
7. 포크 하나당 뮤텍스를 걸어서 포크의 중복을 방지한다.  

- 1차 구현 완료 : 24.5.14  
  - 처음에는 뮤텍스 개념을 잘 이해하지 못해 3번이나 다시 제작했다.

-  성능 개선
  -  각 출력마다 뮤텍스를 만들어서 출력에 걸리는 뮤텍스락을 분산시켰다.  
  -  데드락을 방지하기 위해 짝수 번호부터 포크를 들기 시작하고, 짝수가 다 들면 뮤텍스를 풀어서 홀수가 들게 했다.(홀수 마지막은 짝수랑 같이 출발 -> 1번과의 경쟁 방지)

### 2. Bonus  
1. 파싱은 맨데토리와 동일하게 진행, info 구조체는 philo에 안 넣고 따로 들고다님.
2. 출력 권한, 포크 개수, 시작 시간 조정, 다 먹었는지 확인하는 세마포어를 각각 들고다닌다.
3. 모두 동일한 시간에 출방하기 위해 포크 실행하는 while문 전에 시작 시간을 저장하고, while문 한 번에 평균적으로 100us정도 걸리는 것을 확인해서,
   인원수 * 100 + 5ms를 보정값으로 시작시간에 더해줬다. 그리고 포크 뜨고 프로세스 실행하고 시작시간으로부터 인원수 * 100 + 5ms만큼 시간이 지날 때까지 busy wait을 통한 usleep 실행.
4. 보너스도 홀수 먼저 시작하고 짝수는 세마포어를 걸어두고 홀수 한 명이 포크를 다 잡으면 짝수 한 명이 출발하는 방식으로 데드락을 방지했다.
5. 메인 프로세스는 인원 수만큼 sem_wait으로 기다리고 철학자가 자신의 할당량만큼 다 먹는 순간 sem_post를 해주면 다 먹었는지 확인하는 세마포어가 인원 수 만큼 반복되면 메인프로세스는 동작이 실행된다.
   메인 프로세스의 동작이 실행되면 kill명령어로 자식 프로세스를 하나씩 죽인다. (ac=5인 경우는 sem_wait을 인원 수보다 더 많이 기다려서 부모 프로세스의 모드 동작을 멈춘다)
6. 한 프로세스가 굶으면 굶었다는 메세지 출력하면서 출력 세마포어를 sem_post를 해주지 않아 모든 프로세스의 출력을 통제한다. 그리고 다 먹었는지 확인하는 세마포어의 값을 인원수 + 1만큼 증가시켜서 메인 프로세스의 코드가 동작하게 한다.

- 어려웠던 부분
  - 세마포어는 open으로 만들 때 첫 번째 인자로 넣어준 문자열을 저장하여 같은 문자열로는 세마포어를 생성하지 않게 막는다. 따라서 같은 문자열로 세마포어를 또 생성하려고 하는 경우는 sem_unlink를 종료 전에 실행해줘야 한다. 안정적인 방법으로는 unlink는 세마포어 실행에 영향을 주지 않기 때문에 open 직후에 nulink를 해주면 좋다.
