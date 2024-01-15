function updateTime() {
    const currentDate = new Date();
    const options = {
      weekday: 'long',
      year: 'numeric',
      month: 'long',
      day: 'numeric',
      hour: '2-digit',
      minute: '2-digit',
      second: '2-digit',
      hour12: false
    };

    const formattedDate = new Intl.DateTimeFormat('en-US', options).format(currentDate);
    const timeElement = document.getElementById('time');
    timeElement.innerHTML = formattedDate;
  }
  updateTime();
  setInterval(updateTime, 1000);

  async function esp32Webserver() {
    try {
      const response = await fetch('http://192.168.1.89/value');
  
      if (!response.ok) {
        throw new Error(`HTTP error! Status: ${response.status}`);
      }
  
      const value = await response.json(); // หรือ response.text() ตามลักษณะข้อมูลที่ได้
      const Temperature = document.getElementById('Temperature');
      const Fahrenheit = document.getElementById('Fahrenheit');
      const Humidity = document.getElementById('Humidity');

      Temperature.innerHTML = value.Temperature.toFixed(2);
      Fahrenheit.innerHTML = value.Fahrenheit.toFixed(2);
      Humidity.innerHTML = value.Humidity.toFixed(2);

      //console.log(value);
    } catch (error) {
      console.error('Error:', error);
    }
  }
  
  esp32Webserver();
  setInterval(esp32Webserver, 1000);

  async function Led1(led1) {
    const esp_led1 = document.getElementById(led1).checked;
    try {
      const result1 = await fetch('http://192.168.1.89/led1', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/x-www-form-urlencoded',
      },
      body: `data=${esp_led1}`
    });
    const val1 = await result1.json(); 
    console.log(val1.res);
    } catch (error) {
      console.log(error);
    }
  }


  async function Led2(led1) {
    const esp_led2 = document.getElementById(led1).checked;
    try {
      const result2 = await fetch('http://192.168.1.89/led2', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/x-www-form-urlencoded',
      },
      body: `data=${esp_led2}`
    });
    const val2 = await result2.json(); 
    console.log(val2.res);
    } catch (error) {
      
    }
  }