package pl.kurs.requests;

public class AppointmentRequest {
    private String date;
    private String room_number;
    private String prescription;
    private String choose_patient;
    private String choose_doctor;
    private String choose_disease;

    public String getDate() {
        return date;
    }

    public void setDate(String date) {
        this.date = date;
    }

    public String getRoom_number() {
        return room_number;
    }

    public void setRoom_number(String room_number) {
        this.room_number = room_number;
    }

    public String getPrescription() {
        return prescription;
    }

    public void setPrescription(String prescription) {
        this.prescription = prescription;
    }

    public String getChoose_patient() {
        return choose_patient;
    }

    public void setChoose_patient(String choose_patient) {
        this.choose_patient = choose_patient;
    }

    public String getChoose_doctor() {
        return choose_doctor;
    }

    public void setChoose_doctor(String choose_doctor) {
        this.choose_doctor = choose_doctor;
    }

    public String getChoose_disease() {
        return choose_disease;
    }

    public void setChoose_disease(String choose_disease) {
        this.choose_disease = choose_disease;
    }

    @Override
    public String toString() {
        return "AppointmentRequestData{" +
                "date='" + date + '\'' +
                ", room_number='" + room_number + '\'' +
                ", prescription='" + prescription + '\'' +
                ", choose_patient='" + choose_patient + '\'' +
                ", choose_doctor='" + choose_doctor + '\'' +
                ", choose_disease='" + choose_disease + '\'' +
                '}';
    }
}
