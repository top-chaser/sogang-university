Phase 3 : run processes in background in your shell

### 구현 내용

#### 명령어 구현

- cd : 특정 디렉터리로 이동
- ls : 디렉터리의 내용물 출력
- mkdir : 디렉터리 생성
- rmdir : 디렉터리 삭제
- touch : 파일 생성
- cat : 파일 내용 출력
- echo : 파일 내용 출력
- exit : 쉘 종료
- quit : 쉘 종료
- | : 한 프로세스의 출력을 다른 프로세스의 입력으로 사용
- jobs : 백그라운드에 있는 작업 목록 출력
- bg : 중지되어있는 백그라운드 작업을 백그라운드에서 실행하거나 포그라운드에 있는 작업을 포그라운드로 옮김
- fg : 백그라운드 작업을 포그라운드로 옮겨서 실행
- kill : 특정 작업에게 신호를 보냄
- & : 프로세스를 백그라운드로 실행

#### 기타 구현

- ', ", \`가 짝수 번 사용되었다면 (', ", \`로 둘러 쌓였다면) 그 사이에 있는 내용물의 의미를 제거
- echo \`pwd\`와 같은 명령어는 파이프를 이용해 구현
- split_pipe 함수를 통해 파이프로 연결된 명령어를 분리 (이 때, 파이프가 없다면 호출이 되지 않으므로 굳이 예외처리를 하지 않음)
- kill의 경우 보통의 리눅스와 같이 사용가능하고 이에 더해 %를 이용해 원하는 프로세스를 종료할 수 있음