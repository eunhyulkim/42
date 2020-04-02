# 소인수분해(Factorization)
by **eunhkim**

---
## what is factorization?
[나무위키](https://namu.wiki/w/%EC%86%8C%EC%9D%B8%EC%88%98%EB%B6%84%ED%95%B4)에 따르면,

> 1. **소인수분해**란 **합성수**를 **소수**들의 곱으로 나타내는 것을 말한다.
> 2. **합성수**란 여러 소수(素數)들이 곱셈으로 합쳐져서 이루어진 수를 말한다. 즉, 임의의 자연수 n에 대해 1과 자기 자신을 제외한 다른 약수가 존재할 때, 이 수를 합성수라고 한다.
> 3. **소수**란 1과 자기 자신으로밖에 나누어지지 않는 정수를 말한다.

---
## what is subject?
[서브젝트](https://docs.google.com/document/d/1utPkD1rfZIes4dv-Q1qKJThB8bmmQk8u7O1FGjhdO2Y)에 따르면,

> 어떤 숫자 하나를 명령어 라인에서 인자로 입력했을 때, 해당 숫자를 **소인수 분해**하여 **결과적으로 나오는 소수**들을 **작은 수에서 큰 수의 순서대로 딱 한번씩만 차례로 출력**하는 프로그램을 짜야 합니다.

---
## what is error?
[서브젝트](https://docs.google.com/document/d/1utPkD1rfZIes4dv-Q1qKJThB8bmmQk8u7O1FGjhdO2Y)에 따르면,

> 입력되는 수는 **1보다 큰 32bit unsigned integer**로, 즉 **2부터 2^32-1까지**입니다. **그 밖의 입력**에 대해서는 에러 메시지를 출력하세요. 그리고 **기타 가능한 모든 경우의 에러**에 대해서도 합당한 에러 메시지를 출력하세요.

---
## Norm is needed?
[ 쓰레드](https://42born2code.slack.com/archives/CU6MTFBNH/p1585725942298400)에 따르면,

> Libft 사용이 가능한가요?
> Norm을 지켜야 하나요?
> 소스 파일은 1개밖에 못 만드나요?

라는 질문에 보컬의 대답이 없으므로, **지키기로.** 파일은 1개, 함수는 5개, 각 함수는 25줄 이하, libft는 사용하지 않기로. 물론 printf도.

----
## How to solve?
1. **인자**를 받는다.
2. 문자를 **숫자**로 바꾼다.
3. **소인수분해**를 한다. 소인수가 발견될 때마다 **즉시 출력**한다.
4. 프로세스 도중 에러가 발견될 경우 **합당한 에러 메시지를 출력**하고 **프로그램을 즉시 종료**한다.


----
## Which algortihm?
소인수분해 알고리즘으로는 윌리엄, 폴라드 로, 페르마의 알고리즘 등이 있겠지만 이번 테스트의 평가 관점은 **읽고 고치기 쉬운 Readable**이니까, 단순하게 나눌 대상이 1이 될 때까지 **가장 작은 소수인 2부터 나눠간다.** 주어진 수의 제곱근까지 한 번도 나누어지지 않는다면 소수이므로 더 이상 볼 것 없이 종료한다.

자료구조는 스택을 쓰고 중복을 제거한 후 정렬하여 순서대로 출력할 수 있겠지만 놈(Norm) 제약도 빡빡하고 이번 테스트의 평가 관점은 **읽고 고치기 쉬운 Readable**이니까, **소인수가 발견될 때마다 즉시 출력**한다. 어차피 오름차순 분해이므로, 중복을 피하기 위해 직전에 출력한 숫자 하나만 저장해뒀다가 출력할 때 비교한다.

----
## Result
    $ ./factorization +64
    > 2

    $ ./factorization 9240
    > 2 3 5 7 11

    $ ./factorization 4294967294
    > 2 2147483647

----
## Exception Handling
**case 1.** 인자가 **없을** 때

    $ ./factorization
    > argument count is invalid

**case 2.** 인자가 **1개 이상**일 때

    $ ./factorization 42 94
    > argument count is invalid

**case 3.** 인자가 **음수**일 때

    $ ./factorization -24
    > factorization does not treat negative number

**case 4.** 인자에 **'+'** 기호가 **2개 이상**일 때

    $ ./factorization ++10
    > argument contains non-numeric character

**case 5.** 인자가 **숫자가 아닌 문자를 포함**할 때

    $ ./factorization 124c
    > argument contains non-numeric character

**case 6.** 인자가 **주어진 범위를 초과**할 때

    $ ./factorization 124c
    > argument is out of range

**case 7.** 인자가 **주어진 범위에 미치지 못할** 때

    $ ./factorization 0
    > argument must be greater than 1

    $ ./factorization 1
    > argument must be greater than 1

----
## Other Check-point
* 주어진 인자가 **소수**일 경우 아무것도 출력해서는 안 된다.
* 같은 소인수가 여러 번 존재하더라도 **한 번만 출력**해야 한다.
* 마지막 소인수를 출력한 다음 **개행**되어야 한다.
* 첫 번째 소인수 앞, 마지막 소인수 뒤에 **공백**이 없어야 한다.

----
## Validation Tip
[2~9999의 소인수분해 목록](https://m.blog.naver.com/PostView.nhn?blogId=483pky&logNo=221193148861&proxyReferer=http%3A%2F%2F168.126.130.229%2Ftm%2F%3Fa%3DCR%26b%3DMAC%26c%3D300020963651%26d%3D32%26e%3D2203%26f%3DbS5ibG9nLm5hdmVyLmNvbS80ODNwa3kvMjIxMTkzMTQ4ODYx%26g%3D1585817314251%26h%3D1585817314308%26y%3D0%26z%3D0%26x%3D1%26w%3D2019-07-24%26in%3D2203_1748_00023587%26id%3D20200402)을 참고해 작은 수의 범위에서 답이 맞게 나오는지 확인하고, [소수 목록](https://ko.wikipedia.org/wiki/%EC%86%8C%EC%88%98_%EB%AA%A9%EB%A1%9D)의 큰 소수들을 적당히 곱해 큰 수의 범위에서 답이 맞게 나오는지 확인한다. 테스트 프로그램을 따로 만들면 좋겠지만 과연 에너지가...?
