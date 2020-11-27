# 12주차

## 문제 1

### 문제설명

여러 가구 사이에 전화를 설치하기 위해 전화회사에 작업을 맡겼는데 설치한 전화선의 길이에 비례하여 설치비를 받는다고 한다.<br>
악덕 전화회사에서는 최대한 비용이 많이 들게 하여 많은 돈을 받으려고 할 것이다.<br>
모든 가구를 연결하며 최대의 비용으로 전화회선을 설치할 수 있는 최대신장트리를 구하라.<br>
<br>
입력의 첫째줄에는 가구의 수(20 이하의 정수)를 입력받는다.<br>
인접행렬과 비슷한 개념으로 가구 사이에 설치해야하는 전화선의 길이(10 이하의 정수)를 행렬로 입력받는다.<br>
<br>
출력은 최대신장트리를 구해서 가중치의 합을 구한다.<br>
<br>
### 실행 화면 예시

<img src="/img/12-1.png" width="60%" height="60%">

### 코드
```c

```

## 문제 2

### 문제설명

다익스트라(Dijkstra) 알고리즘이란 단일 시작점 최단경로 알고리즘으로, 시작 정점에서부터 다른 정점까지의 최단 거리를 구하는 알고리즘이다. <br>
이 알고리즘을 이용하여 주어진 출발점과 어느 한 정점을 지나 도착점에 도달하는 최단거리를 구하는 프로그램을 작성하라.<br>
제일 먼저 테스트 케이스의 개수(T<=5)를 입력받는다. 그다음 노드의 개수 N(3<=N<=20)과 간선의 개수 E(1<=E<=100)를 입력받는다. 그 다음 E 줄에 걸쳐 연결된 간선과 그 간선의 가중치(<=100)를 입력받는다. 여기서 가중치란 비용으로 인식하여 가중치가 적을수록 비용이 적게 드는 것이다.
마지막 줄에는 출발점 S, 꼭 지나야하는 정점 A, 그리고 도착점 F를 차례로 입력받는다.<br>
위의 입력을 바탕으로 어느 한 정점을 꼭 지나 출발점과 도착점 사이의 최단 경로 비용을 출력하는 프로그램을 작성하라. 경로비용은 경로상의 모든 간선들의 가중치의 합이고, 최단경로는 경로비용이 가장 작은 경로이다. 경로가 존재하지 않으면 -1을 출력하라. 단, 지났던 정점을 다시 지나갈 수 있다.<br>
<br>
### 실행 화면 예시

<img src="/img/12-2.png" width="60%" height="60%">

### 코드
```c

```

## 문제 3

### 문제설명

시장에 버섯을 팔아 돈을 버는 Teemo는 오늘도 버섯을 채집하기 위해 산에 오른다.<br>
하지만 무서운 늑대가 산에 존재하기 때문에 날이 저물기 전에 산에서 내려오려고 한다.<br>
Teemo는 산의 지도를 보면서 자신이 가장 높이 올라 갔다가 내려올 수 있는 위치를 알아내고 싶다.<br>
<br>
Teemo의 집은 지도의 좌상단인(0,0)에 위치해 있다.<br>
산의 높이는 A-Z로 표현되어 있고 0-25까지의 높이를 의미한다.<br>
Teemo는 인접한 좌표이면 상하좌우, 대각선 어디로든지 이동할 수 있다.<br>
<br>
낮은 곳에서 높은 곳으로 이동할 때는 높이 차이의 제곱만큼의 시간이 걸리지만 높은 곳에서 낮은 곳으로 이동할때는 1시간만 걸린다. 높이가 동일한 곳으로의 이동 시간은 0이라고 가정한다.<br>
* A에서 C로 이동하려면 4시간(A->C는 2만큼 차이가 나고 2를 제곱하면 4가 됨), C에서 A로 이동할 때는 1시간(C->A로 내려오는 것이므로)이 걸린다.<br>
단, 높이 차이가 너무 큰 곳은 올라갈 수도 내려갈 수도 없다.<br>
<br>
산의 크기와 지도, 날이 저물기까지 남은 시간, 넘을 수 있는 최대 높이가 주어질 때<br>
Teemo가 다녀올 수 있는 가장 높은 곳의 높이를 출력하라. (Z가 가장 높은 곳이라면 25가 된다.)<br>

* Teemo는 집에서 출발해서 집으로 돌아 와야 한다.<br>
* 입력 첫 줄은 [가로 X, 세로 Y, 한 번에 오르거나 내려 올 수 있는 최대 높이 H, 날이 저물기까지 남은 시간 T]이다. 여기에서 X와 Y는 10 이하의 정수이고, H는 25 이하의 정수이며, T는 100 이하의 정수이다.<br>
* 다음 줄 부터는 X행 Y열 크기의 지도 행렬이 주어진다.<br>

<br>
단, 입력은 한 개 이상의 테스트케이스가 아래와 같이 반복해서 나올 수 있다.<br>

### 실행 화면 예시

<img src="/img/12-3.png" width="60%" height="60%">

### 코드
```c

```