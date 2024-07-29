import React, { useContext, useEffect, useState } from 'react';
import '../css/ServiceOrder.css';
import ApiClient from '../service/ApiClient';
import userContext from '../PageInfo';
import Vehicle from "../entity/Vehicle";
import { Link } from 'react-router-dom';

const ServiceOrder = () => {
  const apiClient = new ApiClient();
  const { userId } = useContext(userContext);
  const [ownedCars, setOwnedCars] = useState<Vehicle[]>([]);
  const [loading, setLoading] = useState<boolean>(true);
  const [error, setError] = useState<string | null>(null);

  useEffect(() => {
    const fetchClientVehicles = async () => {
      try {
        const vehicles = await apiClient.GetClientVehicles(userId);
        setOwnedCars(vehicles);
      } catch (err) {
        setError("Error fetching client vehicles");
      } finally {
        setLoading(false);
      }
    };

    fetchClientVehicles();
  }, [userId]);

  if (loading) {
    return <div>Loading...</div>;
  }

  if (error) {
    return <div>{error}</div>;
  }

  return (
    <div id="serviceOrderContainer">
      <table>
        <thead>
          <tr>
            <th>Brand</th>
            <th>Model</th>
            <th>Modifications</th>
            <th>Inspection Date</th>
            <th>Price</th>
            <th></th>
            <th></th>
          </tr>
        </thead>
        <tbody>
          {ownedCars.map((car, index) => (
            <tr key={index}>
              <td>{car.brand}</td>
              <td>{car.model}</td>
              <td>{car.modifications}</td>
              <td>{car.next_inspection_date}</td>
              <td>${car.price.toLocaleString()}</td>
              <td><Link className="nav-button" to={"/carDetails/" + car.vehicle_id} >Details</Link></td>
              <td><Link className="nav-button" to={"/orderServiceSelected/:" + car.vehicle_id} >Order Service</Link></td>
            </tr>
          ))}
        </tbody>
      </table>
    </div>
  );
};

export default ServiceOrder;