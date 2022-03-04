- 주차관리 시스템 (Parking Management System)

  

  개발 기간: 2022-02-26 ~ 2022-03-04 (1 주)

  참여인원  3 명

  기술스택: C

  

  **Description**

  주차장 관리를 위한 프로그램으로 차량의 입출차를 관리하고, 주차장 내 현황, 정산 기능 등을 제공한다. 또한 회원가입, 로그인 기능을 제공하여 주차장 별로 관리를 할 수 있도록 만들었다.

  

  **Environment**

  OS: Linux 

  Windows 기반의 WSL2나 ubuntu, 라즈비안 등 리눅스 기반의 OS 필요하다. 가상환경이나 네이티브나 상관은 없어보이나 아래 환경에서만 테스트해보았다.

  - Windows11, WSL2
  - 라즈베리파이 가상환경, QEMU(kernel-qemu-4.4.34-jessie), Raspbian(2019-06-20-raspbian-buster)

  Compiler

  - gcc - WSL 혹은 raspbian(Raspberry Pi OS)에서 직접 컴파일

  

  **Prerequisite**

  1. `Makefile`

     linux or wsl: `gcc`  (default)

  2. `~/.bashrc` 에 라이브러리 경로 등록

     - 프로그램에 필요한 공유, 동적 라이브러리는 lib 폴더에 포함되어 있다.

     1. `vi ~/.bashrc`연 뒤 맨 아래에 추가
        - `export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$HOME/lib` 
        - 클론한 주소는 모두 다르므로 lib 디렉토리를 정확히 설정한다.
     2. `source ~/.bashrc` 으로 적용

  3. 파일 준비

     1. git clone 

     2. 프로그램 실행시 `data/user.dat` 파일이 꼭 필요하므로 만약 파일이 없다면 빈 파일을 생성한다. 

        `touch ./data/user.dat`

     3. 더미데이터 등록(optional)

        - `data-*.tar.gz` 와 이름이 비슷한 압축 파일은 더미데이터이다. 압축을 해제하고 내부 내용을 `data` 폴더 안에 넣어주면 더미데이터가 등록된다.
        - 압축 해제 명령어`tar -xvzf data-2120.tar.gz`

  

  **Run**

  프로그램 실행

  ```shell
  make
  ./main
  ```

  - Makefile을 사용해서 컴파일을 한 뒤 프로그램을 실행한다.

  

  **Directories and Files**

  ```
  data/
   ├ admin/      (dummy data)
   │ ├ Current.dat
   │ ├ History.dat
   │ ├ histroy.log
   │ ├ ParkingLot.dat
   │ └ User.dat
   ├ test1/      (dummy data)
   ├ ...         (dummy data)
   ├ test20/     (dummy data)
   └ user.dat (Required)
  include/
  lib/
  src/
  ```

  - `data`: 프로그램 실행시 사용하는 데이터가 저장되어있는 폴더
    - `data/user.dat` 에 등록되어있는 아이디를 기준으로 각각의 폴더를 구성함
    - `Current.dat`: 주차되어있는 차량 정보. 프로그램 실행 시 리스트 생성,  종료 시 백업.
    - `History.dat`: 프로그램에서 사용하는 데이터 파일
    - `histroy.log`: 유저가 읽을 수 있는 기록 파일
    - `ParkingLot.dat`: 주차장의 정보가 있는 파일
    - `User.dat`: 차주 정보. 프로그램 실행 시 해시테이블 생성,  종료 시 저장 백업.
  - `include`: 헤더파일만 모아둔 폴더
  - `lib`: 공유, 동적 라이브러리를 모아둔 폴더
  - `src` :실제 코드(.c)를 모아둔 폴더
