# 10주차

## 문제 1

### 문제설명

<교재 61번 문제와 동일, 단, 교재에 있는 소스코드는 오류가 있으므로 그대로 사용하면 문제 발생><br>
<br>
줄다리기는 두 편에 있는 사람들이 서로 반대 방향으로 밧줄을 잡아당기는, 힘을 겨루는 시합이다. <br>
자기편 쪽으로 밧줄을 끌어오는 데 성공한 편이 경기에 이기게 된다.<br>
사무실 야유회에서 줄다리기를 하기로 했다. 야유회에 참가한 사람들을 두 편으로 공평하게 나눈다.<br>
모든 사람들이 둘 중 한 편에 참여해야 하며, 두 편의 사람 수는 한 명이 넘게 차이가 나면 안 된다.<br>
그리고 양 편에 속한 사람들 체중의 총합 차를 최소한으로 줄여야 한다.<br>
<br>
첫번째 줄에는 테스트 케이스의 수가 입력되고, 그 다음 줄은 빈줄이 입력된다.<br>
각 케이스의 첫번째 줄에는 야유회에 참가한 사람의 수인 n이 입력된다.<br>
그 밑으로 n줄에 걸쳐서 사람들의 체중이 입력된다. (체중은 1 ≤ 체중 ≤ 450인 정수)<br>
총 사람수는 최대 100명이고, 서로 다른 테스트 케이스 사이에는 빈 줄이 하나씩 입력된다.<br>
<br>
각 테스트 케이스마다 한 줄씩의 결과를 출력하며, 각 줄마다 두 개씩의 정수가 출력되어야 한다.<br>
<br>
첫번째 수는 왼편에 속한 사람들의 체중의 총합<br>
다른 수는 다른 편에 속한 사람들의 체중의 총합<br>
이 두 값이 서로 다르면 작은 값을 먼저 출력<br>
두 개의 서로 다른 케이스에 대한 결과는 빈 줄로 구분한다. <br>

### 실행 화면 예시

<img src="/img/10-1.png" width="60%" height="60%">

### 코드
```c

```

## 문제 2

### 문제설명

박스의 몸체 부분을 b(ox), 덮개 부분을 c(over)이라고 하자.<br>
상자에서 물건이 흘러가나가는 일이 없도록 포장하려면 몸체를 두고 덮개로 덮어야 한다. 이 경우를 "합당한 상태"라고 정의한다.<br>
상자 안에 상자가 들어가는 경우 역시 합당한 상태라고 할 수 있다.<br>
입력으로 0 이상 12 이하의 정수인 n이 주어지면 n개의 상자로 만들 수 있는 모든 합당한 상태를 출력하라.<br>
합당한 상태를 출력하는 순서는 사전순이다. bcbcbc를 bbbccc로 바꿔서 출력하라는 의미가 아니라<br>
bbbccc가 bbcbcc보다 먼저 출력하라는 의미이다.<br>
아래의 입출력 예시를 참고하자.<br>
### 실행 화면 예시

<img src="/img/10-2.png" width="60%" height="60%">

### 코드
```c

```

## 문제 3

### 문제설명

어떤 채굴회사가 광산에서 다이아몬드 채굴작업을 시작하려고 한다.<br>
이 회사는 이동비용을 절감하기위해 채굴을 시작하기에 앞서 다이아몬드가 매장되어있는 곳의 구역을 번호매기기로했다.<br>
NxN 크기로 주어진 지도에서 1로 표시된 부분이 다이아몬드가 매장되어 있는 곳의 좌표이다.<br>
다이아몬드가 서로 인접해 있는 곳을 한 구역으로 정의한다. <br>
여기서 인접이라는 것은 상하 또는 좌우로 다이아몬드가 연결되어 있는 것을 이야기한다.대각선상에 있는 경우는 인접한 것이 아니다.<br>
<br>
좌측 최상단부터 탐색을 수행하며, 탐색은 첫째 줄부터 탐색한 후 첫째 줄에서의 구역 탐색이 끝나면 둘째 줄의 탐색을 수행한다.<br>
탐색 중에 먼저 발견한 채굴지역부터 구역 번호를 매겨서 지도에 표시를 한다.<br>
아래 광산지도에서는 구역이 2개로 표시되는데 구역 번호는 1번과 2번이 된다.<br>
단, 지도의 크기는 10*10까지이다.<br>
### 실행 화면 예시

<img src="/img/10-3.png" width="60%" height="60%">

### 코드
```c

```