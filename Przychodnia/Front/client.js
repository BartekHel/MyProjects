function findNumber(dane) {
    for(var i = 0; i < dane.length; i++) {
        if(dane[i] == " ") {
            return i
        }
    }
}

async function myfunc() {
    const response = await fetch("http://localhost:8080/take/doctor/1");
    const doctor = await response.text()
    console.log(doctor);
    document.getElementById("temp").innerText = doctor
}

async function showTable(tableName, url) {
    const tab = document.getElementById(tableName)
    tab.innerHTML = ""
    const response = await fetch("http://localhost:8080/take/" + url)
    var responseData = await response.text()
    console.log(responseData)
    responseData = responseData.replace(/[\[\]"]/g, '')
    const responseList = responseData.split(",")
    responseList.forEach(element => {
        const row = tab.insertRow()
        const cell = row.insertCell(0)

        cell.innerText = element.substring(findNumber(element))
    })
}

async function addDoctor(fname, lname, spec) {
    const firstName = document.getElementById(fname).value
    const lastName = document.getElementById(lname).value
    const specialization = document.getElementById(spec).value
    if(firstName == "" || firstName == null || lastName == "" || lastName == null || specialization == "" || specialization == null) {
        alert("Nie zostawiaj pustych pól!")
        return
    }
    const urlstr = "http://localhost:8080/take/doctor/" + firstName + "/" + lastName + "/" + specialization
    const response = await fetch(urlstr, {mode: 'cors'})
    const message = await response.text()
    alert(message)
}

async function addPatient(fname, lname, address) {
    const firstName = document.getElementById(fname).value
    const lastName = document.getElementById(lname).value
    const patientAddress = document.getElementById(address).value
    if(firstName == "" || firstName == null || lastName == "" || lastName == null || patientAddress == "" || patientAddress == null) {
        alert("Nie zostawiaj pustych pól!")
        return
    }
    const urlstr = "http://localhost:8080/take/patient/" + firstName + "/" + lastName + "/" + patientAddress
    const response = await fetch(urlstr, {mode: 'cors'})
    const message = await response.text()
    alert(message)
}

async function addDisease(name) {
    const diseaseName = document.getElementById(name).value
    if(diseaseName == "" || diseaseName == null) {
        alert("Nie zostawiaj pustych pól!")
        return
    }
    const urlstr = "http://localhost:8080/take/disease/Add=" + diseaseName
    const response = await fetch(urlstr, {mode: 'cors'})
    const message = await response.text()
    alert(message)
}

async function addAppointment(date1, room_number1, prescription1, choose_patient1, choose_doctor1, choose_disease1) {
    const appDate = document.getElementById(date1).value
    const roomNumber = document.getElementById(room_number1).value
    const appPrescription = document.getElementById(prescription1).value

    const selectPatientElement = document.getElementById(choose_patient1)
    const selectDoctorElement = document.getElementById(choose_doctor1)
    const selectDiseaseElement = document.getElementById(choose_disease1)

    if(selectPatientElement == null || selectDoctorElement == null || selectDiseaseElement == null) {
        alert("Nie zostawiaj pustych pól!")
        return
    }

    const selectedPatientIndex = selectPatientElement.selectedIndex
    const selectedPatientOption = selectPatientElement.options[selectedPatientIndex].value

    const selectedDoctorIndex = selectDoctorElement.selectedIndex
    const selectedDoctorOption = selectDoctorElement.options[selectedDoctorIndex].value

    const selectedDiseaseIndex = selectDiseaseElement.selectedIndex
    const selectedDiseaseOption = selectDiseaseElement.options[selectedDiseaseIndex].value

    if(appDate == "" || appDate == null || roomNumber == "" || roomNumber == null || appPrescription == "" || appPrescription == null) {
        alert("Nie zostawiaj pustych pól!")
        return
    }
    console.log(appDate)
    console.log(roomNumber)
    console.log(appPrescription)
    console.log(selectedPatientOption)
    console.log(selectedDoctorOption)
    console.log(selectedDiseaseOption)

    const urlstr = "http://localhost:8080/take/appointment/" + appDate + "/" + roomNumber + "/" + appPrescription + "/" + selectedPatientOption + "/" + selectedDoctorOption + "/" + selectedDiseaseOption
    const response = await fetch(urlstr, {mode: 'cors'})
    const message = await response.text()
    alert(message)

    //fetch("http://localhost:8080/take/appointment/add/", {
    //    method: "POST",
    //    body: JSON.stringify({
    //        date: appDate,
    //        room_number: roomNumber,
    //        prescription: appPrescription,
    //        choose_patient: selectedPatientOption,
    //        choose_doctor: selectedDoctorOption,
    //        choose_disease: selectedDiseaseOption
    //    }),
    //    headers: {
    //        "Content-type": "application/json; charset=UTF-8"
    //    }
    //})
    //.then(response => {
    //    if (!response.ok) {
    //      throw new Error('Network response was not ok');
    //    }
    //    return response.json();
    //  })
    //  .then(data => {
    //    console.log('Odpowiedź z serwera:', data);
    //  })
    //  .catch(error => {
    //    console.error('Wystąpił błąd:', error);
    //});
}

async function fillSelectMenu(name, url) {
    const list = document.getElementById(name)
    const response = await fetch("http://localhost:8080/take/" + url, {mode: 'cors'})
    responseData = await response.text()
    responseData = responseData.replace(/[\[\]"]/g, '')
    const responseList = responseData.split(",")
    responseList.forEach(element => {
        var option = document.createElement("option")
        option.value = element.substring(0, findNumber(element))
        option.text = element.substring(findNumber(element))
        list.appendChild(option)
    });
}

function fillMenu() {
    fillSelectMenu("choose-patient", "patient/listpatients")   
    fillSelectMenu("choose-doctor", "doctor/listdoctors")
    fillSelectMenu("choose-disease", "disease/listdiseases")
}

function showSelected(selectName, tableName, url) {
    const selectElement = document.getElementById(selectName)
    const selectedIndex = selectElement.selectedIndex
    const selectedOption = selectElement.options[selectedIndex].value
    url = url + "/" + selectedOption
    showTable(tableName, url)
}

async function deleteSelected(selectName, url) {
    const selectElement = document.getElementById(selectName)
    const selectedIndex = selectElement.selectedIndex
    const selectedOption = selectElement.options[selectedIndex].value
    url = url + "/" + selectedOption
    const response = await fetch("http://localhost:8080/take/" + url, {mode: 'cors'})
    const responseData = await response.text()
    console.log(responseData)
}