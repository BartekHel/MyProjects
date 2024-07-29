import axios from "axios";
import CarDetails from "../entitiy/CarDetail";
import Vehicle from "../entitiy/Vehicle";
import Service from "../entitiy/Service"
import Order from "../entitiy/Order";



export const axiosInstance= axios.create({
     baseURL: "http://localhost:8080/car-shop",
  });

  class ApiClient{
    baseURL:string= "http://localhost:8080/car-shop";
    constructor(){        
      }


    getImage=(car_id:number)=>{
      return axiosInstance.get(this.baseURL+`/vehicles/${car_id}/picture`)
      .then((response)=>response.data);
    }

    buyCarByDealer=(price:number,client_token:string,dealer_id:number,showroomId:number,vehicle_id:number)=>{
       return axiosInstance.post(this.baseURL+'/orders/createorderbytoken',
      {price:price,client_token:client_token,dealer_id:dealer_id,showroom_id:showroomId,vehicle_id:vehicle_id});
    }

    buyCar=(price:number,client_id:number,dealer_id:number,showroomId:number,vehicle_id:number)=>{
      return axiosInstance.post(this.baseURL+'/orders/createorder',
     {price:price,client_id:client_id,dealer_id:dealer_id,showroom_id:showroomId,vehicle_id:vehicle_id});
   }

    getCarDetails=async(carId:number)=>{
      return await axiosInstance.get<CarDetails>(this.baseURL+'/vehicles/'+carId).then((response)=>response.data);
    }

    getDealerOrders=async(dealerId:number)=>{
      const orders = await axiosInstance.get(this.baseURL+'/dealer/'+dealerId + '/listorders').then((response)=>response.data);
      console.log( orders);
      return orders.map((order: any) => ({
        order_id: order.first.order_id,
        submission_date: order.first.submission_date,
        delivery_date: order.first.delivery_date,
        vehicle_id: order.second.vehicle_id,
        brand: order.second.brand,
        model: order.second.model,
        price: order.first.price
      }));
    }
    

    Register=async (login:string, password:string, email:string, name:string, surname:string): Promise<[boolean, string, number, string]>=>{
      const resp = await axiosInstance.post('http://localhost:8080/car-shop/users/reg',{login:login, password:password, email:email, role: "CLIENT", name:name, surname:surname})
      
      return [resp.data.success, resp.data.message, resp.data.id, resp.data.login]
    }

    Login = async (login:string, password:string): Promise<[boolean, string, number, string]> =>
    {
      const resp = await axiosInstance.post('http://localhost:8080/car-shop/users/login',{login:login, password:password})
      return [resp.data.success, resp.data.role, resp.data.id, resp.data.login]
    }

    GetLoggedInfo = async (login:string): Promise<[number, string, string, string, string]> =>
    {
      
      const resp = await axiosInstance.get('http://localhost:8080/car-shop/users/'+login);
      console.log(resp);
      
      return [resp.data.id, resp.data.email, resp.data.role, resp.data.name, resp.data.surname]
    }

    GetClientVehicles = async (id: number): Promise<Vehicle[]> => {
      try {
        const resp = await axios.get(`http://localhost:8080/car-shop/client/${id}/listvehicles`);

        console.log(id);
        console.log(resp.data);
    
        return resp.data.map((vehicle: any) => ({
          vehicle_id: vehicle.vehicle_id,
          brand: vehicle.brand,
          model: vehicle.model,
          modifications: vehicle.modifications,
          next_inspection_date: vehicle.next_inspection_date,
          price: vehicle.price
        }));
      } catch (error) {
        console.error("Error fetching client vehicles:", error);
        throw error;
      }
    };

    GetVehicleById = async (id: number): Promise<Vehicle> => {
      try {
        const resp = await axios.get(`http://localhost:8080/car-shop/vehicles/${id}`);

        const vehicle = resp.data;
        console.log("vehicle");
        console.log(vehicle);
        const transformedVehicle = {
          vehicle_id: vehicle.vehicle_id,
          brand: vehicle.brand,
          model: vehicle.model,
          modifications: vehicle.modifications,
          next_inspection_date: vehicle.next_inspection_date,
          price: vehicle.price
        };

        return transformedVehicle;

      } catch (error) {
        console.error("Error fetching client vehicles:", error);
        throw error;
      }
    };
    GetLeastOccupiedReapirer = async (): Promise<[number, string]> =>
    {
      try{
        const resp = await axiosInstance.get('http://localhost:8080/car-shop/repairer/leastoccupied');
        console.log([resp.data.repairer_id, resp.data.user.name + " " + resp.data.user.surname])
        return [resp.data.repairer_id, resp.data.user.name + " " + resp.data.user.surname]
      } catch (error) {
        console.error("Error fetching repairer:", error);
        throw error;
      }
      
    };

    PostService = async (vehicle_id: number, repairer_id: number, description: string): Promise<boolean> =>
    {
      const resp = await axiosInstance.post('http://localhost:8080/car-shop/services',{vehicleId:vehicle_id, repairerId:repairer_id, description:description})
      return [resp.data];
    }

    PutVehicleShowroom = async (vehicle_id: number, showroom_id: number) =>
    {
      const resp = await axiosInstance.put('http://localhost:8080/car-shop/vehicles/'+vehicle_id+'/changeshowroom?showroom_id='+showroom_id)
      return resp.data;
    }
    
    getDealerShowroom = async (dealer_id:number): Promise<number> =>
    {
      const resp = await axiosInstance.post('http://localhost:8080/car-shop/services',{vehicleId:vehicle_id, repairerId:repairer_id, description:description})
      return [resp.data.showroom_id];
    }

    GetMechanicServices = async (id: number): Promise<Service[]> => {
      try {
        const resp = await axios.get(`http://localhost:8080/car-shop/repairer/${id}/listservices`);

        console.log(id);
        console.log(resp.data);
    
        return resp.data.map((service: any) => ({
          service_id: service.service_id,
          description: service.description,
          admission_date: service.admission_date,
          execution_date: service.execution_date,
          price: service.price
        }));
      } catch (error) {
        console.error("Error fetching services:", error);
        throw error;
      }
    };

    SetServiceDate = async (service_id: number, date: string) => {
      try {
          const response = await axios.post(
              `http://localhost:8080/car-shop/services/${service_id}/setdate`,
              date,  // Directly sending the date string
              {
                  headers: {
                      'Content-Type': 'application/json',
                  },
              }
          );
          console.log('Data ustawiona pomyślnie:', response.data);
      } catch (error) {
          console.error('Błąd podczas ustawiania daty:', error);
      }
  };

    SetServicePrice = async (service_id: number, price: number) =>
    {
      try {
        const response = await axios.post(
            `http://localhost:8080/car-shop/services/${service_id}/setprice`,
            price, 
            {
                headers: {
                    'Content-Type': 'application/json',
                },
            }
        );
        console.log('Data ustawiona pomyślnie:', response.data);
      } catch (error) {
          console.error('Błąd podczas ustawiania daty:', error);
      }
    };

    GenerateToken = async(clientId: number):Promise<string> =>
    {
      try {
        const response = await axios.get(
            `http://localhost:8080/car-shop/client/${clientId}/generatetoken`
            
        );
        return response.data;
      } catch (error) {
          console.error('Błąd podczas generowania tokenu:', error);
      }
    }
  }

  export default ApiClient;