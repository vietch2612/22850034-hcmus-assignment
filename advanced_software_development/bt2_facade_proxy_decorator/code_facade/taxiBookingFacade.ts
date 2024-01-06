import { GPSService } from "./gpsService";
import { PaymentSystem } from "./paymentSystem";
import { RideService } from "./rideService";

export class TaxiBookingFacade {
  private gpsSerice: GPSService;
  private paymentSystem: PaymentSystem;
  private rideService: RideService;

  constructor() {
    this.gpsSerice = new GPSService();
    this.paymentSystem = new PaymentSystem();
    this.rideService = new RideService();
  }

  bookTaxi(start: string, end: string, fare: number): string {
    const route = this.gpsSerice.findRoute(start, end);
    const ride = this.rideService.bookRide(start, end);
    const payment = this.paymentSystem.processPayment(fare);

    return `${route}\n${ride}\n${payment}`;
  }
}
