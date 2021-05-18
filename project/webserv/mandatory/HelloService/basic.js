$(document).ready(function() {
  $('.ui.dropdown')
    .dropdown()
  ;

  $('.ui.Dropdown').dropdown('setting', 'onChange', function(){
    var message_idx = Number($('.strategy.dropdown').dropdown('get value'));
    switch(message_idx){
      case 0:
        $('.strategy.description').text('마틴게일 시스템은 이겼을 때 꾸준히 미니멈 베팅을 하고, 졌을 때에는 무조건 이전 배팅의 2배를 걸면서 잃은 것을 한 번에 회복하고 미니멈 벳의 이익까지 노리는 배팅 시스템입니다. 총알만 충분하다면 확실하죠.');
        break;
      case 1:
        $('.strategy.description').text('마틴게일+ 시스템은 이겼을 때 꾸준히 미니멈 베팅을 하는 것은 동일하지만, 졌을 때에는 무조건 이전 배팅의 2배에 미니멈 벳 하나 분량을 더 걸면서 잃은 것을 한 번에 회복하고 모든 게임당 미니멈 벳의 이익을 얻은 결과를 노리는 배팅 시스템입니다. 이론적으로라면 플레이한 게임 수*미니멈 벳의 이익이 나옵니다. 마틴게일보다도 총알이 훨씬 더 충분해야겠죠.');
        break;
      case 2:
        $('.strategy.description').text('다니엘 시스템은 이겼을 때 이전 베팅보다 미니멈 벳 하나 분량을 적게 걸고, 졌을 때에는 미니멈 벳 하나 분량을 더 많이 거는 시스템입니다. 승률이 50% 근처라는 전제 하에, 이길 때는 질 때보다 더 많이 얻고, 질 때는 이길 때보다 더 적게 잃습니다. 따라서 수열의 중간에 위치하고 있다면 승률은 50%보다 아래이지만, 그렇다고 반드시 마이너스인 것은 아닙니다.');
        break;
      case 3:
        $('.strategy.description').text('다니엘 리턴 시스템은 이겼을 때 이전 베팅보다 미니멈 벳 하나 분량을 적게 걸고, 졌을 때에는 미니멈 벳 하나 분량을 더 많이 거는 다니엘 시스템과 기본적으로 동일합니다. 다만 엑시트를 하는 시점이 다릅니다. 수열의 왼쪽 끝으로, 미니멈 벳으로 베팅액이 복귀하는 시점까지 게임을 하고 엑시트합니다.');
        break;
      case 4:
        $('.strategy.description').text('파로리8 시스템은 이겼을 때 이전 베팅보다 2배를 걸고, 8연승 후에는 다시 미니멈 벳으로 돌아가며, 졌을 때에는 무조건 미니멈 벳으로 돌아가는 베팅 시스템입니다. 연승에서 패배했을 때에도 한 번 진 것과 같은 금액만 잃기 때문에, 250번 이하의 레이스당 1번의 256배당을 노리는 1/256 시스템입니다.');
        break;
      case 5:
        $('.strategy.description').text('파로리7 시스템은 이겼을 때 이전 베팅보다 2배를 걸고, 7연승 후에는 다시 미니멈 벳으로 돌아가며, 졌을 때에는 무조건 미니멈 벳으로 돌아가는 베팅 시스템입니다. 연승에서 패배했을 때에도 한 번 진 것과 같은 금액만 잃기 때문에, 120번 이하의 레이스당 1번의 128배당을 노리는 1/128 시스템입니다.');
        break;
      case 6:
        $('.strategy.description').text('파로리6 시스템은 이겼을 때 이전 베팅보다 2배를 걸고, 6연승 후에는 다시 미니멈 벳으로 돌아가며, 졌을 때에는 무조건 미니멈 벳으로 돌아가는 베팅 시스템입니다. 연승에서 패배했을 때에도 한 번 진 것과 같은 금액만 잃기 때문에, 60번 이하의 레이스당 1번의 64배당을 노리는 1/64 시스템입니다.');
        break;
      case 7:
        $('.strategy.description').text('파로리5 시스템은 이겼을 때 이전 베팅보다 2배를 걸고, 5연승 후에는 다시 미니멈 벳으로 돌아가며, 졌을 때에는 무조건 미니멈 벳으로 돌아가는 베팅 시스템입니다. 연승에서 패배했을 때에도 한 번 진 것과 같은 금액만 잃기 때문에, 30번 이하의 레이스당 1번의 32배당을 노리는 1/32 시스템입니다.');
        break;
      case 8:
        $('.strategy.description').text('클럽 파로리5 시스템은 이겼을 때 이전 베팅보다 2배에 미니멈 벳 1개 분량을 더 걸고, 5연승 후에는 다시 미니멈 벳으로 돌아가며, 졌을 때에는 무조건 미니멈 벳으로 돌아가는 베팅 시스템입니다. 파로리 시스템을 기준으로 더 높은 확률로 많은 금액을 획득하기 위해 변형된 시스템으로, 연승에서 패배했을 때에는 레이스 당 미니멈 벳이 아니라 게임당 미니멈 벳의 금액을 잃는 리스크가 있습니다.');
        break;
      case 9:
        $('.strategy.description').text('클럽 파로리4 시스템은 이겼을 때 이전 베팅보다 2배에 미니멈 벳 1개 분량을 더 걸고, 4연승 후에는 다시 미니멈 벳으로 돌아가며, 졌을 때에는 무조건 미니멈 벳으로 돌아가는 베팅 시스템입니다. 파로리 시스템을 기준으로 더 높은 확률로 많은 금액을 획득하기 위해 변형된 시스템으로, 연승에서 패배했을 때에는 레이스 당 미니멈 벳이 아니라 게임당 미니멈 벳의 금액을 잃는 리스크가 있습니다.');
        break;
      case 9:
        $('.strategy.description').text('굿맨 시스템은 이겼을 때 최소한의 이익은 남기며 조심스럽게 배팅액을 높여가되, 미니멈 배팅의 다섯 배 이상은 걸지 않고 지면 미니멈 베팅으로 회귀하는 안전한 시스템입니다. 1승 후 바로 패배하지 않는 이상 손실이 거의 없습니다.');
        break;
    }
  });

  // 시뮬레이션 버튼을 눌렀을 때
  $('.ui.large.play.button').on('click', function(event) {
    // input 값 선언
    var budget = Number($('input.budget_v').val())*10000;
    var minbet = Number($('input.minbet_v').val());
    var strategy = Number($('.strategy.dropdown').dropdown('get value'));
    var day = Number($('input.day_v').val());
    var time = Number($('input.time_v').val());
    // ouput 값 선언
    var ruinday = 0;
    var result = 0;
    var gain = 0;
    var result_bool = ['버는', '잃는'];
    var result_bool_val = 0;
    var judge = [''];

    // 임시데이터
    var daily_budget = 0;
    var present_play = 0;
    var prev_wl = '';
    var this_wl = '';
    var prev_bet = 0;
    var this_bet = 0;


    // [0]마틴게일 시스템
    var strategyZero = function(){
      prev_bet = this_bet;
      if(prev_wl == ''){
        // console.log("첫 판은 미니멈 " + minbet + "원 배팅이야.");
        this_bet = minbet;
      }else if(prev_wl == 'w'){
        if(daily_budget < budget){
          if(budget-daily_budget<=daily_budget){
            // console.log("이전 판에서 이겼지만 아직 원금을 회복해야 해.");
            this_bet = budget-daily_budget;
            // console.log(budget + "원까지 만회하기 위해 " + this_bet + "원을 걸어보겠어.");
          }else{
            // console.log("이전 판에서 이겼지만 아직 원금을 회복해야 해.");
            this_bet = daily_budget;
            // console.log(budget + "원까지 만회할 돈은 없어서 남은 전재산인" + this_bet + "원이라도 걸어보겠어.");
          }
        }else{
          this_bet = minbet;
          // console.log("이전 판에서 이겼으니 정석대로 " + minbet + "원을 다시 걸겠어.");
        }
      }else if(prev_wl == 'l'){
        if(present_play == 60*time){
          present_play -= 1;
        }

        if(prev_bet*2 <= daily_budget){
          this_bet = prev_bet*2;
          // console.log("이전 판에서 졌으니 두 배로 걸겠어. " + this_bet + "원 말이야.");
        }else{
          this_bet = daily_budget;
          // console.log("이전 판에서 졌지만 두 배로 걸 돈이 없네. 전 재산인 " + this_bet + "원이라도 걸어야지.");
        }
      }else if(prev_wl == 'd'){
        if(daily_budget < budget){
          present_play -= 1;
        }
        this_bet = prev_bet;
        // console.log("이전 판에서 비겼으니 그대로 " + this_bet + "원을 걸겠어.");
      }

      if(this_wl == 'w'){
        // console.log("그리고 이겼지.");
        daily_budget += this_bet;
      }else if(this_wl == 'l'){
        // console.log("그리고 져버렸어.");
        daily_budget -= this_bet;
      }else{
        // console.log("그리고 비겼어.")
      }
        // console.log(daily_budget + "원이 이제 내 전 재산이야.");
    };

    // [1]마틴게일+(1-3-7-15) 시스템
    var strategyOne  = function(){
      prev_bet = this_bet;
      if(prev_wl == ''){
        // console.log("첫 판은 미니멈 " + minbet + "원 배팅이야.");
        this_bet = minbet;
      }else if(prev_wl == 'w'){
        if(daily_budget < budget){
          if(budget+minbet-daily_budget<=daily_budget){
            // console.log("이전 판에서 이겼지만 아직 원금을 회복해야 해.");
            this_bet = budget+minbet-daily_budget;
            // console.log(budget + "원까지 만회하기 위해 " + this_bet + "원을 걸어보겠어.");
          }else{
            // console.log("이전 판에서 이겼지만 아직 원금을 회복해야 해.");
            this_bet = daily_budget;
            // console.log(budget + "원까지 만회할 돈은 없어서 남은 전재산인" + this_bet + "원이라도 걸어보겠어.");
          }
        }else{
          this_bet = minbet;
          // console.log("이전 판에서 이겼으니 정석대로 " + minbet + "원을 다시 걸겠어.");
        }
      }else if(prev_wl == 'l'){
        if(present_play == 60*time){
          present_play -= 1;
        }

        if(prev_bet*2+minbet <= daily_budget){
          this_bet = prev_bet*2+minbet;
          // console.log("이전 판에서 졌으니 두 배로 걸겠어. " + this_bet + "원 말이야.");
        }else{
          this_bet = daily_budget;
          // console.log("이전 판에서 졌지만 두 배로 걸 돈이 없네. 전 재산인 " + this_bet + "원이라도 걸어야지.");
        }
      }else if(prev_wl == 'd'){
        if(daily_budget < budget){
          present_play -= 1;
        }
        this_bet = prev_bet;
        // console.log("이전 판에서 비겼으니 그대로 " + this_bet + "원을 걸겠어.");
      }

      if(this_wl == 'w'){
        // console.log("그리고 이겼지.");
        daily_budget += this_bet;
      }else if(this_wl == 'l'){
        // console.log("그리고 져버렸어.");
        daily_budget -= this_bet;
      }else{
        // console.log("그리고 비겼어.")
      }
        // console.log(daily_budget + "원이 이제 내 전 재산이야.");
    };

    // [2]다니엘(승리시 1감소, 패배시 1증가) 시스템
    var strategyTwo  = function(){
      prev_bet = this_bet;
      if(prev_wl == ''){
        // console.log("첫 판은 미니멈 " + minbet + "원 배팅이야.");
        this_bet = minbet;
      }else if(prev_wl == 'w'){
        if(prev_bet-minbet>minbet){
            this_bet = prev_bet - minbet;
          }else{
            this_bet = minbet;
          }
      }else if(prev_wl == 'l'){
        if(prev_bet+minbet <= daily_budget){
          this_bet = prev_bet+minbet;
        }else{
          this_bet = daily_budget;
        }
      }else if(prev_wl == 'd'){
        this_bet = prev_bet;
      }

      if(this_wl == 'w'){
        daily_budget += this_bet;
      }else if(this_wl == 'l'){
        daily_budget -= this_bet;
      }
    }

    // [3]다니엘 리턴(승리시 1감소, 패배시 1증가, minbet으로 복귀 후 종료) 시스템
    var strategyThree  = function(){
      prev_bet = this_bet;
      if(prev_wl == ''){
        // console.log("첫 판은 미니멈 " + minbet + "원 배팅이야.");
        this_bet = minbet;
      }else if(prev_wl == 'w'){
        if(prev_bet-minbet>minbet){
            this_bet = prev_bet - minbet;
            if(present_play==60*time){
              present_play -= 1;
            }
          }else{
            this_bet = minbet;
          }
      }else if(prev_wl == 'l'){
        if(present_play==60*time){
          present_play -= 1;
        }
        if(prev_bet+minbet <= daily_budget){
          this_bet = prev_bet+minbet;
        }else{
          this_bet = daily_budget;
        }
      }else if(prev_wl == 'd'){
        this_bet = prev_bet;
        if(this_bet>minbet){
          if(present_play==60*time){
            present_play -= 1;
          }
        }
      }

      if(this_wl == 'w'){
        daily_budget += this_bet;
      }else if(this_wl == 'l'){
        daily_budget -= this_bet;
      }
    }

    // [4]파로리8(승리시 2배 배팅, 실패시 mibet으로 북귀) 시스템
    var strategyFour  = function(){
      prev_bet = this_bet;
      if(prev_wl == ''){
        this_bet = minbet;
      }else if(prev_wl == 'w'){
        if(prev_bet >= 120*minbet){
          this_bet = minbet;
        }else if(prev_bet*2<=daily_budget){
          this_bet = prev_bet*2;
        }else{
          this_bet = daily_budget;
        }
      }else if(prev_wl == 'l'){
        if(minbet < daily_budget){
          this_bet = minbet;
        }else{
          this_bet = daily_budget;
        }
      }else if(prev_wl == 'd'){
        this_bet = prev_bet;
      }

      if(this_wl == 'w'){
        daily_budget += this_bet;
      }else if(this_wl == 'l'){
        daily_budget -= this_bet;
      }
    }

    // [5]파로리7(승리시 2배 배팅, 실패시 mibet으로 북귀) 시스템
    var strategyFive  = function(){
      prev_bet = this_bet;
      if(prev_wl == ''){
        this_bet = minbet;
      }else if(prev_wl == 'w'){
        if(prev_bet >= 60*minbet){
          this_bet = minbet;
        }else if(prev_bet*2<=daily_budget){
          this_bet = prev_bet*2;
        }else{
          this_bet = daily_budget;
        }
      }else if(prev_wl == 'l'){
        if(minbet < daily_budget){
          this_bet = minbet;
        }else{
          this_bet = daily_budget;
        }
      }else if(prev_wl == 'd'){
        this_bet = prev_bet;
      }

      if(this_wl == 'w'){
        daily_budget += this_bet;
      }else if(this_wl == 'l'){
        daily_budget -= this_bet;
      }
    }

    // [6]파로리6(승리시 2배 배팅, 실패시 mibet으로 북귀) 시스템
    var strategySix  = function(){
      prev_bet = this_bet;
      if(prev_wl == ''){
        this_bet = minbet;
      }else if(prev_wl == 'w'){
        if(prev_bet >= 30*minbet){
          this_bet = minbet;
        }else if(prev_bet*2<=daily_budget){
          this_bet = prev_bet*2;
        }else{
          this_bet = daily_budget;
        }
      }else if(prev_wl == 'l'){
        if(minbet < daily_budget){
          this_bet = minbet;
        }else{
          this_bet = daily_budget;
        }
      }else if(prev_wl == 'd'){
        this_bet = prev_bet;
      }

      if(this_wl == 'w'){
        daily_budget += this_bet;
      }else if(this_wl == 'l'){
        daily_budget -= this_bet;
      }
    }

    // [7]파로리5(승리시 2배 배팅, 실패시 mibet으로 북귀) 시스템
    var strategySeven  = function(){
      prev_bet = this_bet;
      if(prev_wl == ''){
        this_bet = minbet;
      }else if(prev_wl == 'w'){
        if(prev_bet >= 15*minbet){
          this_bet = minbet;
        }else if(prev_bet*2<=daily_budget){
          this_bet = prev_bet*2;
        }else{
          this_bet = daily_budget;
        }
      }else if(prev_wl == 'l'){
        if(minbet < daily_budget){
          this_bet = minbet;
        }else{
          this_bet = daily_budget;
        }
      }else if(prev_wl == 'd'){
        this_bet = prev_bet;
      }

      if(this_wl == 'w'){
        daily_budget += this_bet;
      }else if(this_wl == 'l'){
        daily_budget -= this_bet;
      }
    }

    // [8]클럽 파로리5(승리시 2배+1 배팅, 실패시 mibet으로 북귀) 시스템
    var strategyEight  = function(){
      prev_bet = this_bet;
      if(prev_wl == ''){
        this_bet = minbet;
      }else if(prev_wl == 'w'){
        if(prev_bet >= 30*minbet){
          this_bet = minbet;
        }else if(prev_bet*2+1<=daily_budget){
          this_bet = prev_bet*2+1;
        }else{
          this_bet = daily_budget;
        }
      }else if(prev_wl == 'l'){
        if(minbet < daily_budget){
          this_bet = minbet;
        }else{
          this_bet = daily_budget;
        }
      }else if(prev_wl == 'd'){
        this_bet = prev_bet;
      }

      if(this_wl == 'w'){
        daily_budget += this_bet;
      }else if(this_wl == 'l'){
        daily_budget -= this_bet;
      }
    }

    // [9]클럽 파로리4(승리시 2배+1 배팅, 실패시 mibet으로 북귀) 시스템
    var strategyNine  = function(){
      prev_bet = this_bet;
      if(prev_wl == ''){
        this_bet = minbet;
      }else if(prev_wl == 'w'){
        if(prev_bet >= 14*minbet){
          this_bet = minbet;
        }else if(prev_bet*2+1<=daily_budget){
          this_bet = prev_bet*2+1;
        }else{
          this_bet = daily_budget;
        }
      }else if(prev_wl == 'l'){
        if(minbet < daily_budget){
          this_bet = minbet;
        }else{
          this_bet = daily_budget;
        }
      }else if(prev_wl == 'd'){
        this_bet = prev_bet;
      }

      if(this_wl == 'w'){
        daily_budget += this_bet;
      }else if(this_wl == 'l'){
        daily_budget -= this_bet;
      }
    }

    // [10]굿맨(135555) 시스템
    var strategyTen  = function(){
      prev_bet = this_bet;
      if(prev_wl == ''){
        this_bet = minbet;
      }else if(prev_wl == 'w'){
        if(prev_bet < 3){
          this_bet = prev_bet + 1;
        }else if(prev_bet*2+1<=daily_budget){
          this_bet = prev_bet*2+1;
        }else{
          this_bet = daily_budget;
        }
      }else if(prev_wl == 'l'){
        if(minbet < daily_budget){
          this_bet = minbet;
        }else{
          this_bet = daily_budget;
        }
      }else if(prev_wl == 'd'){
        this_bet = prev_bet;
      }

      if(this_wl == 'w'){
        daily_budget += this_bet;
      }else if(this_wl == 'l'){
        daily_budget -= this_bet;
      }
    }

    var strategy_list = [strategyZero, strategyOne, strategyTwo, strategyThree, strategyFour, strategyFive, strategySix, strategySeven, strategyEight, strategyNine, strategyTen];

    var newDayGame = function(){
      present_play = 0;
      daily_budget = budget;
      prev_wl = '';
      this_wl = '';
      prev_bet = 0;
      this_bet = 0;

      var newPlay = function(){
        present_play += 1;
        prev_wl = this_wl;
        var temp_wl_data = Math.floor(Math.random()*100);
        if(temp_wl_data > 54){
          this_wl = 'w';
        }else if(temp_wl_data < 45){
          this_wl = 'l';
        }else{
          this_wl = 'd'
        };
        strategy_list[strategy]();
      };

      for(;;){
        newPlay();
        if(daily_budget<=0){
          ruinday += 1;
          break;
        }else if(present_play==time*60){
          break;
        }
      }
      if(daily_budget>0){
        result += daily_budget;
      }
    }

    var newFullGame = function(){
      var present_day = 1;
      while(present_day <= day){
        newDayGame();
        present_day += 1;
      }
      if(day-ruinday == 0){
        gain = 0;
      }else{
        gain = ((result/(day-ruinday))-budget)/10000;
      }
      result = result-(day*budget);
      if(result>0){
        result_bool_val = 0;
      }else{
        result_bool_val = 1;
      }

      return{
        ruinday: ruinday,
        result: Math.floor(result),
        gain: gain.toFixed(2),
        result_bool: result_bool[result_bool_val],
        judge: judge
      };
    };

    var fullGame = newFullGame();

    // #결과값 입력하기
    $('#ruinday').text(fullGame.ruinday);
    $('#gain').text(fullGame.gain);
    $('#result').text(fullGame.result);
    $('#allday').text(day);
    $('#result_bool').text(fullGame.result_bool);
    $('#judge').text(fullGame.judge[0]);

    // 결과값 나타내기
    $('#result_container').css('visibility', 'visible');
  });

  // 다시 시뮬레이션하기 버튼을 눌렀을 때
  $('.ui.large.replay.button').on('click', function(event) {
    location.reload();
  });
});
