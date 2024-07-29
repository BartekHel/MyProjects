import axios from "axios";
import Vehicle from "../entitiy/Vehicle";
import Employee from "../entitiy/Employee";
import { axiosInstance } from "./ApiClient";

  class ApiAdd{
    constructor(){}

    AddVehicle = async (vehicle: Vehicle) => {
      try {
        const response = await axios.post('http://localhost:8080/car-shop/vehicles', {
          brand: vehicle.brand,
          model: vehicle.model,
          modifications: null,
          price: vehicle.price,
          showroomId: vehicle.showroomId
        });
        return response.data;
      } catch (error) {
        console.error("Error adding the vehicle:", error);
        throw error;
      }
    };
    
    AddEmployee = async (employee: Employee) => {
      try {
        const resp = await axiosInstance.post('http://localhost:8080/car-shop/users/reg',
          {login:employee.email, password:employee.password, email:employee.email, role: employee.role, name:employee.name, surname:employee.surname})
        return resp.data;
      } catch (error) {
        console.error("Error adding the employee:", error);
        throw error;
      }
    };

    ReplaceEmployee = async (id: number, employee: Employee) => {
      try {
        const payload = {
          user_id: id,
          login: employee.login,
          password: employee.password,
          email: employee.email,
          role: employee.role,
          name: employee.name,
          surname: employee.surname
        };
        const resp = await axiosInstance.put(`http://localhost:8080/car-shop/users/${id}`, payload);
        return resp.data;
      } catch (error) {
        console.error("Error replacing the employee:", error);
        throw error;
      }
    };

    ChangeRole = async (employee: Employee) => {
      try {
        const { login, role } = employee;
        const resp = await axiosInstance.put(`http://localhost:8080/car-shop/users/chngrole/${login}`, role, {
          headers: {
            'Content-Type': 'application/json'
          }
        });
        
        return resp.data;
      } catch (error) {
        console.error("Error changing the role:", error);
        throw error;
      }
    };    
    
    DeleteEmployee = async (id: number) => {
      try {
          const resp = await axios.delete(`http://localhost:8080/car-shop/users/${id}`);
          return resp.data;
      } catch (error) {
          console.error("Error deleting the employee:", error);
          throw error;
      }
    };

    DeleteCar = async (id: number) => {
      try {
          const resp = await axios.delete(`http://localhost:8080/car-shop/vehicles/${id}`);
          return resp.data;
      } catch (error) {
          console.error("Error deleting the employee:", error);
          throw error;
      }
    };

    GetUser = async (user: Employee) => {
      try {
          const login = user.login;
          const resp = await axios.get(`http://localhost:8080/car-shop/users/${login}`);
          return resp.data;
      } catch (error) {
          console.error("Error getting the user data:", error);
          throw error;
      }
    };
  }

  export default ApiAdd;