import React, { useContext, useEffect, useState } from 'react';
import '../css/DealersTransactions.css';
import ApiClient from '../service/ApiClient';
import userContext from '../PageInfo';
import Order from '../entitiy/Order';
import { Link } from 'react-router-dom';

const DealersTransactions = () => {
  const apiClient = new ApiClient();
  const { userId } = useContext(userContext);
  const [ orders, setOrders] = useState<Order[]>([]);
  const [loading, setLoading] = useState<boolean>(true);
  const [error, setError] = useState<string | null>(null);

  const fetchOrders = async () => {
    try {
      const orders = await apiClient.getDealerOrders(userId);
      console.log(orders);
      setOrders(orders);
    } catch (err) {
      setError("Error fetching dealers transactions");
    } finally {
      setLoading(false);
    }
  };

  useEffect(() => {
    fetchOrders();
  }, [userId]);

  if (loading) {
    return <div id="serviceOrderContainer">Loading...</div>;
  }

  if (error) {
    return <div id="serviceOrderContainer">{error}</div>;
  }

  const handleDetailsClick = (service) => {
    
  };

  return (
    <div id="serviceOrderContainer">
      <table>
        <thead>
          <tr>
            <th>Brand</th>
            <th>Model</th>
            <th>Submission Date</th>
            <th>Delivery Date</th>
            <th>Price</th>
            <th>Details</th>
          </tr>
        </thead>
        <tbody>
          {orders.map((order, index) => (
            <tr key={index}>
              <td>{order.brand}</td>
              <td>{order.model}</td>
              <td>{order.submission_date}</td>
              <td>{order.delivery_date}</td>
              <td>{order.price}</td>
              <td><Link className="nav-button" to={"/carDetails/" + order.vehicle_id} >Details</Link></td>
            </tr>
          ))}
        </tbody>
      </table>
    </div>
  );
};

export default DealersTransactions;