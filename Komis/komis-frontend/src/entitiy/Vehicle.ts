export default interface Vehicle {
    vehicle_id: number;
    brand: string;
    model: string;
    modifications: string | null;
    next_inspection_date: string;
    price: number;
    showroomId: number;
    
  }