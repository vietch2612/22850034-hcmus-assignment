import { TaxiService } from "./taxiService";
import { RealTaxiService } from "./newTaxiService";

export class ProxyTaxiService implements TaxiService {
  private realService: RealTaxiService;

  constructor() {
    this.realService = new RealTaxiService();
  }

  bookRide(start: string, end: string): string {
    // Add additional checks or functionalities here before delegating to the real service
    const isValidBooking = this.performValidation(start, end);
    if (isValidBooking) {
      return this.realService.bookRide(start, end);
    } else {
      return "Invalid booking request";
    }
  }

  private performValidation(start: string, end: string): boolean {
    // Simulate validation logic
    return start !== end;
  }
}
