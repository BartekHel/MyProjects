export default interface Order {
    order_id: number;
    submission_date: string;
    delivery_date: string;
    price: number;
    vehicle_id: number;
    brand: string;
    model: string;
  }